#include <Arduino.h>
#include "time_face.h"
#include "events.h"
#include "globals.h"

void TimeFace::loop(uint8_t event)
{
  if (event == TICK_EVENT)
    drawTime(false);
}

void TimeFace::drawTime(bool forceRedraw)
{
  bool minChanged = forceRedraw || time.min != prevTime.min;
  bool secHiChanged = forceRedraw || time.sec / 10 != prevTime.sec / 10;

  // Update full time if minute has changed
  // Could save some more updating, but because colon is at start of buffer,
  // and we'll change last two digits, partial update would no longer be cheaper anyway.
  if (minChanged)
  {
    uint8_t hourLo = time.hour % 10;
    uint8_t hourHi = time.hour / 10;
    uint8_t minLo = time.min % 10;
    uint8_t minHi = time.min / 10;
    if (hourHi == 0)
      lcd.buffer[2] = 0;
    else
      lcd.buffer[2] = digits[hourHi];
    lcd.buffer[3] = digits[hourLo];
    lcd.buffer[4] = digits[minHi];
    lcd.buffer[5] = digits[minLo];
  }

  // Last digit: symbols for 10-seconds
  if (secHiChanged)
  {
    uint8_t secHi = time.sec / 10;
    uint8_t secVal = secHi == 0 ? 0 : 0b00100000; // Dot
    for (uint8_t i = 1; i <= secHi; ++i)
      secVal |= digits[i + 9];
    lcd.buffer[6] = secVal;
  }

  lcd.buffer[1] = ((time.sec % 2) == 0) ? 0 : OSO_INDICATOR_COLON;

  // Update the least we can
  if (!minChanged)
  {
    // Update colon
    lcd.show_partial(1, 1);
    // Less often, update seconds symbol too
    if (secHiChanged)
      lcd.show_partial(6, 1);
  }
  // Minute has changed: update whole display
  else
    lcd.show();
}
