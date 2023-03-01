#include <Arduino.h>
#include "tune_face.h"
#include "events.h"
#include "globals.h"

// 0: finetune seconds
static uint8_t screen;
static uint8_t buf[7];
static int16_t tuneVal;
static uint32_t timeoutStart;

static void drawTune();

void TuneFace::enter()
{
  screen = 0;
  timeoutStart = time.totalSeconds;
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
    if (time.totalSeconds - timeoutStart > TIMEOUT_SECONDS)
      return RET_HOME;
    drawTune();
  }
  return RET_STAY;
}

static void drawTune()
{
  // "Draw" into new buffer
  memset(buf, 0, 7);

  buf[4] = digits[0];
  buf[5] = digits[time.sec / 10] | 0b00100000;
  buf[6] = digits[time.sec % 10];

  // Flush if different
  if (memcmp(buf, lcd.buffer, 7) != 0)
  {
    memcpy(lcd.buffer, buf, 7);
    lcd.show();
  }
}
