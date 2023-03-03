#include <Arduino.h>
#include "DS18B20.h"

// Adapted from Davide Gironi's "A DS18B20 1-wire digital thermometer AVR ATmega library"
// https://davidegironi.blogspot.com/2014/09/a-ds18b20-1-wire-digital-thermometer.html

#define DS18B20_PORT PORTD
#define DS18B20_DDR DDRD
#define DS18B20_PIN PIND
#define DS18B20_DQ PD0

static void writeBit(uint8_t bit)
{
  // low for 1uS
  DS18B20_PORT &= ~(1 << DS18B20_DQ); // low
  DS18B20_DDR |= (1 << DS18B20_DQ);   // output
  _delay_us(1);

  // if we want to write 1, release the line (if not will keep low)
  if (bit)
    DS18B20_DDR &= ~(1 << DS18B20_DQ); // input

  // wait 60uS and release the line
  _delay_us(60);
  DS18B20_DDR &= ~(1 << DS18B20_DQ); // input
}

static uint8_t readBit(void)
{
  uint8_t bit = 0;

  // low for 1uS
  DS18B20_PORT &= ~(1 << DS18B20_DQ); // low
  DS18B20_DDR |= (1 << DS18B20_DQ);   // output
  _delay_us(1);

  // release line and wait for 14uS
  DS18B20_DDR &= ~(1 << DS18B20_DQ); // input
  _delay_us(14);

  // read the value
  if (DS18B20_PIN & (1 << DS18B20_DQ))
    bit = 1;

  // wait 45uS and return read value
  _delay_us(45);
  return bit;
}

uint8_t DS18B20::reset()
{
  uint8_t i;

  // low for 480us
  DS18B20_PORT &= ~(1 << DS18B20_DQ); // low
  DS18B20_DDR |= (1 << DS18B20_DQ);   // output
  _delay_us(480);

  // release line and wait for 60us
  DS18B20_DDR &= ~(1 << DS18B20_DQ); // input
  _delay_us(60);

  // get value and wait 420us
  i = (DS18B20_PIN & (1 << DS18B20_DQ));
  _delay_us(420);

  // return the read value, 0=ok, 1=error
  return i;
}

void DS18B20::write(uint8_t val)
{
  uint8_t i = 8;
  while (i--)
  {
    writeBit(val & 1);
    val >>= 1;
  }
}

uint8_t DS18B20::read()
{
  uint8_t i = 8, n = 0;
  while (i--)
  {
    n >>= 1;
    n |= (readBit() << 7);
  }
  return n;
}
