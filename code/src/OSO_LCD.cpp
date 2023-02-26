#include "OSO_LCD.h"
#include <Wire.h>

const PROGMEM uint8_t CHARS[] = {
    0b00000000, // [space]
    0b00101100, // !
    0b01001000, // "
    0b11001010, // # (°)
    0b01010101, // $ (Like an L with an extra segment, use $J to make a W)
    0b01000100, // %
    0b11011000, // & (Like an F without a cross stroke, use &7 to make an M)
    0b00001000, // '
    0b11010001, // (
    0b10001101, // )
    0b00000000, // * (Currently unused)
    0b01010010, // +
    0b00000100, // ,
    0b00000010, // -
    0b00100000, // .
    0b00001100, // /
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
    0b00000000, // : (RESERVED: special character that turns on the colon)
    0b01000000, // ; (Like the apostrophe, but on the other side, use 'foo; to say ‘foo’)
    0b00010001, // <
    0b00000011, // =
    0b00000101, // >
    0b10011010, // ?
    0b11111111, // @
    0b11011110, // A
    0b01010111, // B
    0b00010011, // C
    0b00011111, // D
    0b11010011, // E
    0b11010010, // F
    0b11001111, // G
    0b01010110, // H
    0b00010000, // I
    0b00011101, // J
    0b11010110, // K
    0b01010001, // L
    0b11011100, // M
    0b00010110, // N
    0b00010111, // O
    0b11011010, // P
    0b11001110, // Q
    0b00010010, // R
    0b11000101, // S
    0b01010011, // T
    0b00010101, // U
    0b01011101, // V
    0b01011111, // W
    0b01011110, // X
    0b01001111, // Y
    0b10011001, // Z
};

OSO_LCD::OSO_LCD(void)
{
  memset(this->buffer, 0, 7);
}

bool OSO_LCD::begin(uint8_t _addr)
{
  this->_addr = _addr;
  this->_write_cmd(0b00111100); // Configure for lowest power consumption
  this->_write_cmd(0b01001000); // display ON, 1/3 bias

  return true;
}

void OSO_LCD::show(void)
{
  _write(this->buffer, 7);
}

void OSO_LCD::fill(bool on)
{
  for (int i = 0; i < 6; i++)
  {
    this->buffer[i + 1] = on ? 0xFF : 0x00;
  }
  if (this->auto_write)
    this->show();
}

void OSO_LCD::_write_cmd(uint8_t cmd)
{
  _write(&cmd, 1);
}

void OSO_LCD::_write(const uint8_t *buffer, size_t len)
{
  Wire.beginTransmission(_addr);
  Wire.write(buffer, len);
  Wire.endTransmission(true);
}

void OSO_LCD::_set_buffer(uint8_t pos, uint8_t value)
{
  this->buffer[pos + 1] = value;
}

uint8_t OSO_LCD::_get_buffer(uint8_t pos)
{
  return this->buffer[pos + 1];
}
