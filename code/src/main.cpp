#include <Arduino.h>
#include "OSO_LCD.h"

// CR2032 conservative capacity: 200mAh
// At 50uA: 4000h, or 23 weeks
// CR2: 800mAh
// At 50uA: 16000h, or 95 weeks

#define LED_PIN 3
#define BTN_UP_PIN 17

OSO_LCD lcd;

uint8_t wakeEvent;
bool digitOn = false;
bool btnUpPressed = false;

uint8_t hour = 0;
uint8_t min = 0;
uint8_t sec = 0;

void powerSave();
void onBtnChange();

void setup()
{
  // digitalWrite(LED_PIN, LOW);
  // pinMode(LED_PIN, OUTPUT);

  lcd.begin();

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

  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  btnUpPressed = digitalRead(BTN_UP_PIN) == LOW;

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

  powerSave();
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
  wakeEvent |= 1;
}

static const uint8_t digits[] = {
    0b11011101, // 0
    0b00001100, // 1
    0b10011011, // 2
    0b10001111, // 3
    0b01001110, // 4
    0b11000111, // 5
    0b11010111, // 6
    0b11001100, // 7
    0b11011111, // 8
    0b11001111, // 9
};

void loop()
{
  if (wakeEvent == 1)
  {
    uint8_t hourLo = hour % 10;
    uint8_t hourHi = hour / 10;
    uint8_t minLo = min % 10;
    uint8_t minHi = min / 10;
    uint8_t secLo = sec % 10;
    if (hourHi == 0)
      lcd.buffer[2] = 0;
    else
      lcd.buffer[2] = digits[hourHi];
    lcd.buffer[3] = digits[hourLo];
    lcd.buffer[4] = digits[minHi];
    lcd.buffer[5] = digits[minLo];
    lcd.buffer[6] = digits[secLo];
    lcd.buffer[1] = ((sec % 2) == 0) ? 0 : OSO_INDICATOR_COLON;
    lcd.show();
  }
  else if (wakeEvent == 2)
  {
    if (btnUpPressed)
    {
      digitOn = !digitOn;
      lcd.buffer[2] = digitOn ? 0b11001010 : 0;
      lcd.show();
    }
  }
  powerSave();

  // lcd._buffer[1] = OSO_INDICATOR_COLON;
  // lcd._buffer[2] = 0b11001111;              // 9
  // lcd._buffer[3] = 0b10011011;              // 2
  // lcd._buffer[4] = 0b10001111;              // 3
  // lcd._buffer[5] = 0b01001110 | 0b00100000; // 4 + .
  // lcd._buffer[6] = 0b11000111;              // 5
  // lcd.show();
}

void powerSave()
{
  wakeEvent = 0;
  SMCR = (1 << SM1) + (1 << SM0); // set sleep mode
  cli();
  SMCR |= (1 << SE); // enable sleep
  sei();
  asm("SLEEP");
  // When back: disable sleep
  SMCR &= ~(1 << SE);
}
