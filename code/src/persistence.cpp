#include <Arduino.h>
#include "persistence.h"
#include <EEPROM.h>

void Persistence::saveStaticError(int16_t err)
{
  uint16_t val = (uint16_t)err;
  EEPROM.put(0, val);
}

int16_t Persistence::loadStaticError()
{
  uint16_t val;
  EEPROM.get(0, val);
  // Brand new EEPROM
  if (val == 0xffff)
    return 0;
  return (int16_t)val;
}
