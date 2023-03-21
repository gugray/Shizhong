#include <Arduino.h>
#include "measure_face.h"
#include "events.h"
#include "globals.h"

// 0: temperature 1: uptime
static uint8_t screen;
static uint16_t timeoutStart;

static void drawTemp();
static void drawUptime();

static void resetTimeout();

uint8_t MeasureFace::loop(uint16_t event)
{
  if (ISEVENT(EVT_SECOND_TICK))
  {
    uint16_t elapsed = (totalSeconds & 0xffff) - timeoutStart;
    if (elapsed > TIMEOUT_SECONDS)
      return RET_HOME;
  }

  resetTimeout();

  if (ISEVENT(EVT_ENTER_FACE))
  {
    screen = 0;
    drawTemp();
  }
  else if (ISEVENT(EVT_BTN_MODE_SHORT) || ISEVENT(EVT_BTN_MODE_LONG))
  {
    if (screen == 0 && ISEVENT(EVT_BTN_MODE_SHORT))
      return RET_NEXT;
    screen = (screen + 1) % 2;
    if (screen == 0)
      drawTemp();
    else
      drawUptime();
  }

  return RET_STAY;
}

static void resetTimeout()
{
    timeoutStart = (totalSeconds & 0xffff);
}

static void drawNumber(uint16_t val)
{
  lcd.buffer[4] = digits[val % 10];
  uint8_t vv = val / 10;
  if (vv == 0)
    return;
  lcd.buffer[3] = digits[vv % 10];
  vv /= 10;
  if (vv == 0)
    return;
  lcd.buffer[2] = digits[vv];
}

static void drawTemp()
{
  lcd.fill(false);
  lcd.buffer[5] = 0b11001010; // degree
  lcd.buffer[6] = 0b11010001; // C

  uint16_t val = latestMeasuredTemp / 2;
  drawNumber(val);
  lcd.buffer[4] |= OSO_SYMBOL_DOT;
  lcd.show();
}

static void drawUptime()
{
  uint32_t secs = safeGetTotalSeconds();
  // One day is 86400 seconds
  uint16_t val = secs / 86400;

  lcd.fill(false);
  lcd.buffer[6] = 0b00011111; // d
  drawNumber(val);
  lcd.show();
}

static void drawVoltage()
{
  lcd.fill(false);
  lcd.buffer[5] = 0b00000010;
  lcd.buffer[4] = 0b00000010 | OSO_SYMBOL_DOT;
  lcd.buffer[5] = 0b00000010;
  lcd.buffer[6] = 0b00010101;
  lcd.show();
}
