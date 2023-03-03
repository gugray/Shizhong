#ifndef DSB18B20_H
#define DSB18B20_H

// Works with hard-wired pin: PD0, aka "0" in IDE.
// To change, edit defines at top of CPP file.
struct DS18B20
{
  static uint8_t reset();
  static void write(uint8_t val);
  static uint8_t read();
};

#endif
