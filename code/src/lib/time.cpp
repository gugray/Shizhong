#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "time.h"

void Time::tick()
{
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
