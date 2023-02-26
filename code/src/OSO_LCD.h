#ifndef OSO_LCD_h
#define OSO_LCD_h

#include "Arduino.h"

extern const PROGMEM uint8_t CHARS[];

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
private:
  uint8_t _addr;

public:
  uint8_t buffer[7];
  bool auto_write = true;

public:
  OSO_LCD(void);
  bool begin(uint8_t _addr = 0x3e);
  void show(void);
  void show_partial(uint8_t length, uint8_t pos = 0);
  void fill(bool on);

private:
  void _write(const uint8_t *buffer, size_t len);
  void _write_cmd(uint8_t cmd);
  void _set_buffer(uint8_t pos, uint8_t value);
  uint8_t _get_buffer(uint8_t pos);
};

#endif // OSO_LCD_h
