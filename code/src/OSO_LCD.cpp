#include "OSO_LCD.h"
#include <Wire.h>

const uint8_t digits[] = {
    0b11011101, // 0
    0b00001100, // 1
    0b10011011, // 2
    0b10001111, // 3
    0b01001110, // 4
    0b11000111, // 5
    0b11010111, // 6
    0b11001100, // 7
    0b11011111, // 8
    0b11001111, // 9
    0b01000000, // TL
    0b00001000, // TR
    0b00000010, // MID
    0b00010000, // BL
    0b00000100, // BR
};

OSO_LCD::OSO_LCD()
{
  memset(this->buffer, 0, 7);
}

bool OSO_LCD::begin()
{
  this->_write_cmd(0b00111100); // Configure for lowest power consumption
  this->_write_cmd(0b01001000); // display ON, 1/3 bias

  return true;
}

void OSO_LCD::show_partial(uint8_t pos, uint8_t length)
{
  uint8_t temp[7];
  temp[0] = (pos - 1) * 2;
  memcpy(temp + 1, this->buffer + pos, length);
  _write(temp, length + 1);
}

void OSO_LCD::show(void)
{
  _write(this->buffer, 7);
}

void OSO_LCD::fill(bool on)
{
  for (int i = 0; i < 6; i++)
    this->buffer[i + 1] = on ? 0xFF : 0x00;
}

void OSO_LCD::_write_cmd(uint8_t cmd)
{
  _write(&cmd, 1);
}

void OSO_LCD::_write(const uint8_t *buffer, size_t len)
{
  Wire.beginTransmission(OSO_LCD_I2C_ADDR);
  Wire.write(buffer, len);
  Wire.endTransmission(true);
}
