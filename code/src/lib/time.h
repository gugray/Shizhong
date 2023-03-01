#ifndef TIME_H
#define TIME_H

struct Time
{
  volatile uint32_t totalSeconds = 0;
  volatile uint8_t hour = 0;
  volatile uint8_t min = 0;
  volatile uint8_t sec = 0;

  void tick();
};

#endif
