#include <Arduino.h>
#include "time.h"

void Time::tick()
{
  ++totalSeconds;
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
}
