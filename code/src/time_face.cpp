#include <Arduino.h>
#include "time_face.h"
#include "events.h"
#include "globals.h"

// 0: time; 1: set hour; 2: set minute; 3: set second
static uint8_t screen;
static uint8_t buf[7];
static uint8_t blinkCounter;
static uint16_t timeoutStart;

static void drawTime(bool forceRedraw);
static void drawSetTime();
static void resetSecond();

uint8_t TimeFace::loop(uint16_t event)
{
  if (ISEVENT(EVT_ENTER_FACE))
  {
    screen = 0;
    drawTime(true);
    return RET_STAY;
  }

  // Events on time screen
  if (screen == 0)
  {
    if (ISEVENT(EVT_SECOND_TICK))
      drawTime(false);
    if (ISEVENT(EVT_BTN_MODE_LONG))
    {
      screen = 1;
      faceNeedsQuickTick = true;
      blinkCounter = 0;
      timeoutStart = counter0;
    }
    if (ISEVENT(EVT_BTN_MODE_SHORT))
    {
      return RET_NEXT;
    }
    return RET_STAY;
  }

  // Evertying that's not a tick is user action: reset timout counter
  if (!ISEVENT(EVT_QUICK_TICK) && !ISEVENT(EVT_SECOND_TICK))
    timeoutStart = counter0;

  // Events on set screen
  if (ISEVENT(EVT_BTN_MODE_SHORT) || ISEVENT(EVT_BTN_MODE_LONG))
  {
    screen = (screen + 1) % 4;
    if (screen == 0)
    {
      drawTime(true);
      faceNeedsQuickTick = false;
    }
    return RET_STAY;
  }
  if (ISEVENT(EVT_QUICK_TICK))
  {
    blinkCounter = (blinkCounter + 1) % BLINK_PERIOD;
    if (counter0 - timeoutStart > TIMEOUT_TICKS)
    {
      screen = 0;
      drawTime(true);
      faceNeedsQuickTick = false;
      return RET_STAY;
    }
  }
  if (ISEVENT(EVT_BTN_MINUS_DOWN) || ISEVENT(EVT_BTN_MINUS_REPEAT))
  {
    cli();
    if (screen == 1)
      time.hour = time.hour == 0 ? 23 : time.hour - 1;
    else if (screen == 2)
      time.min = time.min == 0 ? 59 : time.min - 1;
    else
      resetSecond();
    blinkCounter = BLINK_PERIOD / 2;
    sei();
  }
  if (ISEVENT(EVT_BTN_PLUS_DOWN) || ISEVENT(EVT_BTN_PLUS_REPEAT))
  {
    cli();
    if (screen == 1)
      time.hour = (time.hour + 1) % 24;
    else if (screen == 2)
      time.min = (time.min + 1) % 60;
    else
      resetSecond();
    blinkCounter = BLINK_PERIOD / 2;
    sei();
  }
  drawSetTime();
  return RET_STAY;
}

static void resetSecond()
{
  time.sec = 0;
  TIFR2 = 1 << OCF2A; // clear compare match A flag
  TCNT2 = 0;          // clear Timer 2 counter

  // If we mess with seconds here, can't calibrate the next time in tune_face
  lastAdjustedAt = 0;
}

static void drawTime(bool forceRedraw)
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

static void drawSetTime()
{
  // "Draw" into new buffer
  memset(buf, 0, 7);

  // Setting hours or minutes
  if (screen != 3)
  {
    // Draw hours
    if (screen != 1 || (screen == 1 && blinkCounter >= BLINK_PERIOD / 2))
    {
      if (time.hour >= 10)
        buf[2] = digits[time.hour / 10];
      buf[3] = digits[time.hour % 10];
    }
    // Draw minutes
    if (screen != 2 || (screen == 2 && blinkCounter >= BLINK_PERIOD / 2))
    {
      buf[4] = digits[time.min / 10];
      buf[5] = digits[time.min % 10];
    }
    // Colon on/off
    buf[1] = ((time.sec % 2) == 0) ? OSO_INDICATOR_COLON : 0;
  }
  // Setting seconds
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
    buf[5] |= OSO_SYMBOL_DOT;
  }

  // Flush if different
  if (memcmp(buf, lcd.buffer, 7) != 0)
  {
    memcpy(lcd.buffer, buf, 7);
    lcd.show();
  }
}
