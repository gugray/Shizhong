#include <Arduino.h>
#include "set_face.h"
#include "events.h"
#include "globals.h"

#define BLINK_PERIOD 20

uint8_t buf[7];
uint8_t pos;
uint8_t blinkCounter;

void draw()
{
  // "Draw" into new buffer
  memset(buf, 0, 7);

  // When setting hours or minutes
  if (pos != 2)
  {
    // Draw hours
    if (pos != 0 || (pos == 0 && blinkCounter >= BLINK_PERIOD / 2))
    {
      if (time.hour >= 10)
        buf[2] = digits[time.hour / 10];
      buf[3] = digits[time.hour % 10];
    }
    // Draw minutes
    if (pos != 1 || (pos == 1 && blinkCounter >= BLINK_PERIOD / 2))
    {
      buf[4] = digits[time.min / 10];
      buf[5] = digits[time.min % 10];
    }
    // Colon on/off
    buf[1] = ((time.sec % 2) == 0) ? OSO_INDICATOR_COLON : 0;
  }
  // When setting seconds
  else
  {
    // Minutes on the left
    buf[2] = digits[time.min / 10];
    buf[3] = digits[time.min % 10];
    // Seconds on the right, unless blinked hidden
    if (blinkCounter >= BLINK_PERIOD / 2)
    {
      buf[5] = digits[time.sec / 10];
      buf[6] = digits[time.sec % 10];
    }
    // With decimal digit in front
    buf[5] |= 0b00100000;
  }

  // Flush if different
  if (memcmp(buf, lcd.buffer, 7) != 0)
  {
    memcpy(lcd.buffer, buf, 7);
    lcd.show();
  }
}

void SetFace::enter()
{
  pos = 0;
  blinkCounter = 0;
  lcd.fill(false);
  draw();
}

uint8_t SetFace::loop(uint16_t event)
{
  uint8_t ret = RET_STAY;

  if ((event & EVT_QUICK_TICK) != 0)
  {
    blinkCounter = (blinkCounter + 1) % BLINK_PERIOD;
  }

  if ((event & EVT_BTN_MINUS_DOWN) != 0 || (event & EVT_BTN_MINUS_REPEAT) != 0)
  {
    if (pos == 0)
      time.hour = (time.hour + 1) % 24;
    else if (pos == 1)
      time.min = (time.min + 1) % 60;
    else if (pos == 2)
    {
      time.sec = 0;
      TIFR2 = 1 << OCF2A; // clear compare match A flag
      TCNT2 = 0;          // clear Timer 2 counter
    }
    blinkCounter = BLINK_PERIOD / 2;
  }

  if ((event & EVT_BTN_PLUS_DOWN) != 0)
    pos = (pos + 1) % 3;

  draw();

  if ((event & EVT_BTN_MODE_LONG))
    ret = RET_HOME;
  return ret;
}
