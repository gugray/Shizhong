#ifndef OSO_LCD_H
#define OSO_LCD_H

#include "Arduino.h"

#define OSO_LCD_I2C_ADDR 0x3e

extern const uint8_t digits[];

#define OSO_INDICATOR_AM      (0b10000000)
#define OSO_INDICATOR_PM      (0b01000000)
#define OSO_INDICATOR_BATTERY (0b00100000)
#define OSO_INDICATOR_COLON   (0b00010000)
#define OSO_INDICATOR_BELL    (0b00001000)
#define OSO_INDICATOR_WIFI    (0b00000100)
#define OSO_INDICATOR_DATA    (0b00000010)
#define OSO_INDICATOR_MOON    (0b00000001)
#define OSO_INDICATOR_ALL     (0b11101111)

class OSO_LCD
{
public:
  uint8_t buffer[7];

public:
  OSO_LCD();
  bool begin();
  void show();
  void show_partial(uint8_t pos, uint8_t length);
  void fill(bool on);

private:
  void _write(const uint8_t *buffer, size_t len);
  void _write_cmd(uint8_t cmd);
};

#endif
