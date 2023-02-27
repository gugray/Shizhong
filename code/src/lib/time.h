#ifndef TIME_H
#define TIME_H

struct Time
{
public:
  uint32_t totalSeconds = 0;
  uint8_t hour = 0;
  uint8_t min = 0;
  uint8_t sec = 0;

public:
  void tick();
};

#endif
