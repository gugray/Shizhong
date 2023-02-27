#include <Arduino.h>
#include "globals.h"
#include "events.h"
#include "time_face.h"

// Definitions of globals
OSO_LCD lcd;
Time time;
Time prevTime;

// Local vars
uint8_t wakeEvent = 0;
TimeFace timeFace;

// Forward declarations of local functions
void setupTimer2();
void setupButtons();
void setupLowPower();
void powerSave();

void setup()
{
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin();
  timeFace.drawTime(true);

  setupTimer2();
  setupLowPower();

  // Nightie
  powerSave();
}

void loop()
{
  if (wakeEvent != 0)
  {
    timeFace.loop(wakeEvent);
  }
  powerSave();
}

void setupButtons()
{
  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
  pinMode(BTN_MODE_PIN, INPUT_PULLUP);
  PCMSK1 |= bit(PCINT11) | bit(PCINT10) | bit(PCINT8);
  PCIFR |= bit(PCIF1);
  PCICR |= bit(PCIE1);
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

uint8_t debounceCounter = 0;
bool btnUpPressed = false;
bool btnDownPressed = false;
bool btnModePressed = false;

ISR(PCINT1_vect)
{
  uint8_t lastDC = debounceCounter;
  debounceCounter = TCNT2;
  if (lastDC == debounceCounter)
    return;

  bool oldBtnUpPressed = btnUpPressed;
  btnUpPressed = digitalRead(BTN_UP_PIN) == LOW;
  bool oldBtnDownPressed = btnDownPressed;
  btnDownPressed = digitalRead(BTN_DOWN_PIN) == LOW;
  bool oldBtnModePressed = btnModePressed;
  btnModePressed = digitalRead(BTN_MODE_PIN) == LOW;

  if (btnUpPressed && !oldBtnUpPressed)
    wakeEvent = BTN_UP_PRESS_EVENT;
  if (btnDownPressed && !oldBtnDownPressed)
    wakeEvent = BTN_DOWN_PRESS_EVENT;
  if (btnModePressed && !oldBtnModePressed)
    wakeEvent = BTN_MODE_PRESS_EVENT;
}

void setupTimer2()
{
  TCCR2B = 0;                         // stop Timer 2
  TIMSK2 = 0;                         // disable Timer 2 interrupts
  ASSR = (1 << AS2);                  // select asynchronous operation of Timer 2
  TCNT2 = 0;                          // clear Timer 2 counter
  TCCR2A = 0;                         // normal count up mode, no port output
  TCCR2B = (1 << CS21) | (1 << CS22); // start timer: prescaler 256
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)))
    ; // wait for TCN2UB and TCR2BUB to be cleared

  TIFR2 = 1 << OCF2A;   // clear compare match A flag
  OCR2A = 127;          // reaches 128 once per second
  TIMSK2 = 1 << OCIE2A; // enable compare match interrupt

  // TIFR2 = 1 << TOV2;   // clear overflow flag (done by writing a 1 in this bit)
  // TIMSK2 = 1 << TOIE2; // enable overflow interrupt
  TCCR2B = 0;                         // stop Timer 2
  TIMSK2 = 0;                         // disable Timer 2 interrupts
  ASSR = (1 << AS2);                  // select asynchronous operation of Timer 2
  TCNT2 = 0;                          // clear Timer 2 counter
  TCCR2A = 0;                         // normal count up mode, no port output
  TCCR2B = (1 << CS21) | (1 << CS22); // start timer: prescaler 256
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)))
    ; // wait for TCN2UB and TCR2BUB to be cleared

  TIFR2 = 1 << OCF2A;   // clear compare match A flag
  OCR2A = 127;          // reaches 128 once per second
  TIMSK2 = 1 << OCIE2A; // enable compare match interrupt

  // TIFR2 = 1 << TOV2;   // clear overflow flag (done by writing a 1 in this bit)
  // TIMSK2 = 1 << TOIE2; // enable overflow interrupt
}

ISR(TIMER2_COMPA_vect)
{
  TCNT2 = 0;
  prevTime = time;
  time.tick();
  wakeEvent = TICK_EVENT;
}

void powerSave()
{
  wakeEvent = 0;

  // Disable TWI
  TWCR = bit(TWEN) | bit(TWIE) | bit(TWEA) | bit(TWINT);

  SMCR = (1 << SM1) + (1 << SM0); // set sleep mode
  cli();
  SMCR |= (1 << SE); // enable sleep
  sei();
  asm("SLEEP");
  // When back: disable sleep
  SMCR &= ~(1 << SE);
}
