#include <Arduino.h>
#include "globals.h"
#include "events.h"
#include "DS18B20.h"
#include "time_face.h"
#include "tune_face.h"
#include "measure_face.h"

// Definitions of globals
OSO_LCD lcd;
Time time;
Time prevTime;
volatile uint16_t lastMeasuredTemp;
volatile bool faceNeedsQuickTick = false;
volatile uint16_t counter0 = 0;
volatile uint8_t timer2Adjust = 0;
volatile uint8_t dsState = 0;

// Local vars
volatile uint16_t wakeEventMask = 0;

// 0: time; 1: tune
volatile uint8_t faceIx = 0;
TimeFace timeFace;
TuneFace tuneFace;
MeasureFace measureFace;

volatile bool timer0Running = false;
volatile uint16_t btnModePressedAt = 0xffff;
volatile uint16_t btnPlusPressedAt = 0xffff;
volatile uint16_t btnMinusPressedAt = 0xffff;

// Space for temp sensor's scratchpad
uint8_t dsData[9];

// Forward declarations of local functions
void stopTimer0();
void setupTimer0();
void setupTimer2();
void setupButtons();
void setupLowPower();
void goToSleep();
void configureTempSensor();
void startTempConversion();
void readTemp();

void setup()
{
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin();
  timeFace.enter();

  configureTempSensor();
  stopTimer0();
  setupButtons();
  setupTimer2();
  setupLowPower();

  goToSleep();
}

void loop()
{
  uint16_t event;
  // While we handle one set of events, other interrupts might be setting other events
  while (true)
  {
    cli();
    event = wakeEventMask;
    wakeEventMask &= ~event;
    sei();
    if (event == 0)
      break;

    // In SECOND_TICK, handle temp conversion
    if (ISEVENT(EVT_SECOND_TICK))
    {
      // Conversion requested now, and none in progress yet
      if (dsState == 0x01)
      {
        startTempConversion();
        dsState = 0x02;
      }
      // Conversion in progress: finish it!
      else if ((dsState & 0x02) != 0)
      {
        readTemp();
        dsState = 0;
      }
    }

    uint8_t ret;
    if (faceIx == 0)
    {
      ret = timeFace.loop(event);
      if (ret == RET_NEXT)
      {
        faceIx = 1;
        tuneFace.enter();
      }
    }
    else if (faceIx == 1)
    {
      ret = tuneFace.loop(event);
      if (ret == RET_HOME)
      {
        faceIx = 0;
        timeFace.enter();
      }
      else if (ret == RET_NEXT)
      {
        faceIx = 2;
        measureFace.enter();
      }
    }
    else if (faceIx == 2)
    {
      ret = measureFace.loop(event);
      if (ret != RET_STAY)
      {
        faceIx = 0;
        timeFace.enter();
      }
    }
    if (faceNeedsQuickTick)
      setupTimer0();
  }
  goToSleep();
}

void setupLowPower()
{
  // For low power in sleep:
  // Disable BOD: Fuses do this
  // Disable ADC
  ADCSRA = 0;
  // Disable WDT
  cli();
  asm("WDR");
  MCUSR &= ~(1 << WDRF);
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = 0x00;
  sei();
}

void setupTimer2()
{
  TCCR2B = 0;        // stop Timer 2
  TIMSK2 = 0;        // disable Timer 2 interrupts
  ASSR = (1 << AS2); // select asynchronous operation of Timer 2

  // wait for TCN2UB and TCR2BUB to be cleared
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)))
    ;

  TCNT2 = 0;                          // clear Timer 2 counter
  TCCR2A = (1 << WGM21);              // clear timer on compare match, no port output
  TCCR2B = (1 << CS21) | (1 << CS22); // prescaler 256, interrupt enabled

  // wait for TCN2UB and TCR2BUB to be cleared
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)))
    ;

  TIFR2 = 1 << OCF2A;   // clear compare match A flag
  OCR2A = 127;          // reaches 128 once per second
  TIMSK2 = 1 << OCIE2A; // enable compare match interrupt
}

ISR(TIMER2_COMPA_vect)
{
  bool advanceTime = true;
  // When frequency correction is applied, it will be added to "adjust" here
  int8_t adjust = timer2Adjust * 4;

  if (adjust != 0)
  {
    // Note about fine adjustments by messing with counter
    // To turn this into a 4-times-per-second timer, this is needed (verified):
    // TCNT2 = 127 - (32 - 1);
    // When setting a low counter value to shorten a second, the following
    // turns this in to twice-per-second timer (verified):
    // TCNT2 = 64

    // If value is negative: our time is ahead: we're adding an extra delay before incrementing seconds
    if (adjust < 0)
    {
      TCNT2 = 127 + adjust + 1;
      advanceTime = false;
    }
    // Value is positive: our time is behind: we make next cycle shorter
    else
    {
      TCNT2 = adjust;
    }
    timer2Adjust = 0;
  }

  if (advanceTime)
  {
    prevTime = time;
    time.tick();
    wakeEventMask |= EVT_SECOND_TICK;
  }
}

void goToSleep()
{
  // Disable TWI
  TWCR = bit(TWEN) | bit(TWIE) | bit(TWEA) | bit(TWINT);

  // set sleep mode: power save by default, but only idle if timer0 is alive
  // DBG
  if (timer0Running)
    SMCR = 0;
  else
    SMCR = (1 << SM1) + (1 << SM0);

  cli();
  SMCR |= (1 << SE); // enable sleep
  sei();
  asm("SLEEP");

  // When back: disable sleep
  SMCR &= ~(1 << SE);
}

void updateOneButton(volatile uint16_t *pressedAt, uint8_t pin, uint16_t downEventFlag)
{
  // Button is currently pressed
  if (digitalRead(pin) == LOW)
  {
    // Not pressed before
    if (*pressedAt == 0xffff)
    {
      *pressedAt = counter0;
      wakeEventMask |= downEventFlag; // DOWN
    }
    // Was already pressed
    else
    {
      uint16_t elapsed = counter0 - *pressedAt;
      // This is a long press: send once
      if (elapsed == LONG_PRESS_TICKS)
      {
        wakeEventMask |= (downEventFlag << 3); // LONG
        // This is also the first repeat
        wakeEventMask |= (downEventFlag << 1); // REPEAT
      }
      else if (elapsed > LONG_PRESS_TICKS && (elapsed - LONG_PRESS_TICKS) % REPEAT_TICKS == 0)
      {
        wakeEventMask |= (downEventFlag << 1); // REPEAT
      }
    }
  }
  // Button is currently not pressed
  else
  {
    // Was pressed before
    if (*pressedAt != 0xffff)
    {
      // Was it a short press?
      // In the other case, we will have sent out a long press event before
      if (counter0 - *pressedAt < LONG_PRESS_TICKS)
        wakeEventMask |= (downEventFlag << 2); // SHORT
    }
    *pressedAt = 0xffff;
  }
}

bool updateButtons()
{
  updateOneButton(&btnModePressedAt, BTN_MODE_PIN, EVT_BTN_MODE_DOWN);
  updateOneButton(&btnPlusPressedAt, BTN_PLUS_PIN, EVT_BTN_PLUS_DOWN);
  updateOneButton(&btnMinusPressedAt, BTN_MINUS_PIN, EVT_BTN_MINUS_DOWN);

  // Quit timer if no button is pressed
  return btnModePressedAt == 0xffff && btnPlusPressedAt == 0xffff && btnMinusPressedAt == 0xffff;
}

void setupButtons()
{
  pinMode(BTN_MODE_PIN, INPUT_PULLUP);
  pinMode(BTN_PLUS_PIN, INPUT_PULLUP);
  pinMode(BTN_MINUS_PIN, INPUT_PULLUP);
  PCMSK1 |= bit(PCINT11) | bit(PCINT10) | bit(PCINT8);
  PCIFR |= bit(PCIF1);
  PCICR |= bit(PCIE1);
}

void stopTimer0()
{
  timer0Running = false;
  TCCR0B = 0; // Stop Timer 0
  TIMSK0 = 0; // Disable Timer 0 interrupts
  counter0 = 0;
}

void setupTimer0()
{
  if (timer0Running == true)
    return;

  counter0 = 0;
  timer0Running = true;
  TCNT0 = 0;                          // clear Timer 2 counter
  TCCR0A = (1 << WGM01);              // clear timer on compare match, no port output
  TCCR0B = (1 << CS02) | (1 << CS00); // prescaler 1024, interrupt enabled.
                                      // This is from 1 MHz CPU clock! CPU *must* be at 1 MHz.
                                      // 1MHz / 1024 = 976.5625
  TIFR0 = 1 << OCF0A;                 // clear compare match A flag
  OCR0A = 19;                         // reaches 20 about 50x per second
  TIMSK0 = 1 << OCIE0A;               // enable compare match interrupt
}

ISR(TIMER0_COMPA_vect)
{
  ++counter0;
  bool stopTimer = updateButtons();
  // Faces that need the quick tick
  if (stopTimer && !faceNeedsQuickTick)
    stopTimer0();
  wakeEventMask |= EVT_QUICK_TICK;
}

ISR(PCINT1_vect)
{
  // If timer 0 is not running, start it
  // We'll be reading button state in interrupt handler
  setupTimer0();
}

void configureTempSensor()
{
  DS18B20::reset();
  DS18B20::write(0xCC); // Skip ROM
  DS18B20::write(0x4E); // Write scratchpad
  DS18B20::write(0x00); // TH: unused
  DS18B20::write(0x00); // TL: unused
  DS18B20::write(0x20); // Config register for 10-bit resolution (gives us .25C)
}

void startTempConversion()
{
  DS18B20::reset();
  DS18B20::write(0xCC); // Skip ROM
  DS18B20::write(0x44); // Start convesion
}

void readTemp()
{
  DS18B20::reset();
  DS18B20::write(0xCC); // Skip ROM
  DS18B20::write(0xBE); // Read scratchpad
  for (uint8_t i = 0; i < 9; i++)
    dsData[i] = DS18B20::read();
  // Convert the data to actual temperature
  int16_t raw = (dsData[1] << 8) | dsData[0];
  // Zero out lowest two bits, we're using 10-bit resolution
  raw = raw & ~3;
  // This is temp Celsius * 10
  lastMeasuredTemp = raw * 5 / 8;
}
