#include <Arduino.h>
#include "OSO_LCD.h"

// CR2032 conservative capacity: 200mAh
// At 50uA:  4000h, or 23 weeks
// At 20uA: 10000h, or 59 weeks
// CR2: 800mAh
// At 50uA: 16000h, or 95 weeks

#define LED_PIN 3
#define BTN_UP_PIN 17
#define BTN_DOWN_PIN 16
#define BTN_MODE_PIN 14

OSO_LCD lcd;

uint8_t wakeEvent;
bool digitOn = false;
bool btnUpPressed = false;
bool btnDownPressed = false;
bool btnModePressed = false;

uint8_t hour = 0;
uint8_t min = 0;
uint8_t sec = 0;

void setupTimer2();
void powerSave();
void onBtnChange();

void setup()
{
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin();

  setupTimer2();

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

  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
  pinMode(BTN_MODE_PIN, INPUT_PULLUP);
  PCMSK1 |= bit(PCINT11) | bit(PCINT10) | bit(PCINT8);
  PCIFR |= bit(PCIF1);
  PCICR |= bit(PCIE1);

  powerSave();
}

uint8_t x;

ISR(PCINT1_vect)
{
  uint8_t lastX = x;
  x = TCNT2;
  if (lastX != x)
  {
    bool oldBtnUpPressed = btnUpPressed;
    btnUpPressed = digitalRead(BTN_UP_PIN) == LOW;
    bool oldBtnDownPressed = btnDownPressed;
    btnDownPressed = digitalRead(BTN_DOWN_PIN) == LOW;
    bool oldBtnModePressed = btnModePressed;
    btnModePressed = digitalRead(BTN_MODE_PIN) == LOW;

    if (btnUpPressed && !oldBtnUpPressed)
      wakeEvent = 2;
    if (btnDownPressed && !oldBtnDownPressed)
      wakeEvent = 3;
    if (btnModePressed && !oldBtnModePressed)
      wakeEvent = 4;
  }
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

  ++sec;
  if (sec == 60)
  {
    sec = 0;
    ++min;
    if (min == 60)
    {
      min = 0;
      ++hour;
      if (hour == 24)
        hour = 0;
    }
  }
  wakeEvent = 1;
}

bool mdOn = false, upOn = false, dnOn = false;

void loop()
{
  if (wakeEvent == 1)
  {
    uint8_t hourLo = hour % 10;
    uint8_t hourHi = hour / 10;
    uint8_t minLo = min % 10;
    uint8_t minHi = min / 10;
    uint8_t secLo = sec % 10;
    // if (hourHi == 0)
    //   lcd.buffer[2] = 0;
    // else
    //   lcd.buffer[2] = digits[hourHi];
    // lcd.buffer[3] = digits[hourLo];
    // lcd.buffer[4] = digits[minHi];
    // lcd.buffer[5] = digits[minLo];
    lcd.buffer[6] = digits[secLo];
    // lcd.buffer[1] = ((sec % 2) == 0) ? 0 : OSO_INDICATOR_COLON;
    // lcd.show();
    lcd.show_partial(6, 1);
  }
  else if (wakeEvent == 2)
  {
    upOn = !upOn;
    if (upOn)
      lcd.buffer[1] |= OSO_INDICATOR_BELL;
    else 
      lcd.buffer[1] &= ~OSO_INDICATOR_BELL;
    lcd.show_partial(1, 1);
  }
  else if (wakeEvent == 3)
  {
    dnOn = !dnOn;
    if (dnOn)
      lcd.buffer[1] |= OSO_INDICATOR_MOON;
    else 
      lcd.buffer[1] &= ~OSO_INDICATOR_MOON;
    lcd.show_partial(1, 1);
  }
  else if (wakeEvent == 4)
  {
    mdOn = !mdOn;
    if (mdOn)
      digitalWrite(LED_PIN, HIGH);
    else
      digitalWrite(LED_PIN, LOW);
  }
  powerSave();
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
