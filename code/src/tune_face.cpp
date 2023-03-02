#include <Arduino.h>
#include "tune_face.h"
#include "events.h"
#include "globals.h"

// 0: finetune seconds
static uint8_t screen;
static uint8_t buf[7];
static int16_t tuneVal; // Current adjustment in 1/32 seconds
static uint16_t timeoutStart;

static void drawTune();

void TuneFace::enter()
{
  screen = 0;
  tuneVal = 0;
  timeoutStart = (time.totalSeconds & 0xffff);
  drawTune();
}

uint8_t TuneFace::loop(uint16_t event)
{
  // Events on tune screen
  if (ISEVENT(EVT_BTN_MODE_SHORT))
  {
    return RET_NEXT;
  }
  if (ISEVENT(EVT_SECOND_TICK))
  {
    if (tuneVal == 0 && (time.totalSeconds & 0xffff) - timeoutStart > TIMEOUT_SECONDS)
    {
      return RET_HOME;
    }
    drawTune();
  }
  // Everything that's not a tick is user action: reset timeout counter
  else
    timeoutStart = (time.totalSeconds & 0xffff);

  int8_t tnDiff = 0;
  if (ISEVENT(EVT_BTN_MINUS_DOWN) || ISEVENT(EVT_BTN_MINUS_REPEAT))
    tnDiff -= 1;
  if (ISEVENT(EVT_BTN_PLUS_DOWN) || ISEVENT(EVT_BTN_PLUS_REPEAT))
    tnDiff += 1;
  if (tnDiff != 0)
  {
    tuneVal += tnDiff;
    cli();
    timer2Adjust += tnDiff;
    sei();
    drawTune();
  }

  return RET_STAY;
}

static void drawTune()
{
  // "Draw" into new buffer
  memset(buf, 0, 7);

  // Current second
  buf[4] = digits[0];
  buf[5] = digits[time.sec / 10] | OSO_SYMBOL_DOT;
  buf[6] = digits[time.sec % 10];

  // Current adjustment value
  uint16_t tn = tuneVal;
  if (tuneVal < 0)
  {
    buf[2] |= OSO_SYMBOL_DOT; // Minus sign is "dot" before first digit
    tn = -tuneVal;
  }
  if (tn >= 100)
    buf[2] |= digits[tn / 100];
  if (tn >= 10)
  {
    if (tn >= 100)
      tn = tn - 100 * (tn / 100);
    buf[3] = digits[tn / 10];
  }
  buf[4] = digits[tn % 10];

  // Flush if different
  if (memcmp(buf, lcd.buffer, 7) != 0)
  {
    memcpy(lcd.buffer, buf, 7);
    lcd.show();
  }
}
