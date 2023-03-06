#include <Arduino.h>
#include "measure_face.h"
#include "events.h"
#include "globals.h"

static uint16_t timeoutStart;

static void draw();

uint8_t MeasureFace::loop(uint16_t event)
{
  if (ISEVENT(EVT_ENTER_FACE))
  {
    timeoutStart = (totalSeconds & 0xffff);
    draw();
    return RET_STAY;
  }
  if (ISEVENT(EVT_BTN_MODE_SHORT))
  {
    return RET_NEXT;
  }
  if (ISEVENT(EVT_SECOND_TICK))
  {
    uint16_t elapsed = (totalSeconds & 0xffff) - timeoutStart;
    if (elapsed > TIMEOUT_SECONDS)
    {
      return RET_HOME;
    }
    draw();
  }
  return RET_STAY;
}

static void draw()
{
  drawTemperature(latestMeasuredTemp);
}
