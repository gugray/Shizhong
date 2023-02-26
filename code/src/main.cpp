#include <Arduino.h>
#include "OSO_LCD.h"

#define LED_PIN 3

OSO_LCD lcd;
bool ledOn = false;
uint8_t intCount = 0;

void setup()
{
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin();

  TCCR2B = 0;           // stop Timer 2
  TIMSK2 = 0;           // disable Timer 2 interrupts
  ASSR = (1 << AS2);    // select asynchronous operation of Timer 2
  TCNT2 = 0;            // clear Timer 2 counter
  TCCR2A = 0;           // normal count up mode, no port output
  TCCR2B = (1 << CS21); // start timer: prescaler 8, so overflows 16x per sec
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)))
    ;                  // wait for TCN2UB and TCR2BUB to be cleared
  TIFR2 = 1 << TOV2;   // clear overflow flag (done by writing a 1 in this bit)
  TIMSK2 = 1 << TOIE2; // enable overflow interrupt
}

ISR(TIMER2_OVF_vect)
{
  ++intCount;
  if (intCount != 16)
    return;
  intCount = 0;

  ledOn = !ledOn;
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
}

void loop()
{
  delay(500);
  lcd._buffer[1] = OSO_INDICATOR_COLON;
  lcd._buffer[2] = 0b11001111;              // 9
  lcd._buffer[3] = 0b10011011;              // 2
  lcd._buffer[4] = 0b10001111;              // 3
  lcd._buffer[5] = 0b01001110 | 0b00100000; // 4 + .
  lcd._buffer[6] = 0b11000111;              // 5
  lcd.show();
  delay(500);
  lcd.fill(false);
}
