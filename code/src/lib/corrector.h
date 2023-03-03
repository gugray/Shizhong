#ifndef CORRECTOR_H
#define CORRECTOR_H

struct Corrector
{
  static int16_t getStaticError();
  static void setStaticError(int16_t err);

  // Updates the accumulated drift after the last 600-tick period
  // Applies the effect of the static error and the temperature-dependent error
  // avgTem: temperature in Celsius * 100, e.g., 2130 for 21.3 C
  // Returns number of beats to adjust.
  // -> If negative, next second must be shorter, i.e. skip beat(s).
  // -> If positive, we must add extra beat(s) to make a second longer.
  static int8_t periodUpdate(int16_t avgTemp);
};

#endif
