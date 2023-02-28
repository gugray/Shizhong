#include <Arduino.h>
#include "time_face.h"
#include "events.h"
#include "globals.h"

void TimeFace::enter()
{
  drawTime(true);
}

uint8_t TimeFace::loop(uint16_t event)
{
  uint8_t ret = RET_STAY;

  if ((event & EVT_SECOND_TICK) != 0)
    drawTime(false);

  if ((event & EVT_BTN_MODE_SHORT))
    ret = RET_NEXT;

  return ret;
}

void TimeFace::drawTime(bool forceRedraw)
{
  bool minChanged = forceRedraw || time.min != prevTime.min;
  bool quartMinChanged = forceRedraw || time.sec / 15 != prevTime.sec / 15;

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

  // Last digit: quarter-minute circle at top
  if (quartMinChanged)
  {
    uint8_t q = time.sec / 15;
    uint8_t secVal = 0b10000000; // top
    if (q >= 1)
      secVal |= 0b00001000;
    if (q >= 2)
      secVal |= 0b00000010;
    if (q >= 3)
      secVal |= 0b01000000;
    lcd.buffer[6] = secVal;
  }

  // Colon on/off
  lcd.buffer[1] = ((time.sec % 2) == 0) ? OSO_INDICATOR_COLON : 0;

  // Update the least we can
  if (!minChanged)
  {
    // Update colon
    lcd.show_partial(1, 1);
    // Less often, update seconds symbol too
    if (quartMinChanged)
      lcd.show_partial(6, 1);
  }
  // Minute has changed: update whole display
  else
    lcd.show();
}
