#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "corrector.h"

#define MILLION 1000000

static int16_t staticError = 0;
static int32_t accumulatedDrift = 0;

int16_t Corrector::getStaticError()
{
  return staticError;
}

void Corrector::setStaticError(int16_t err)
{
  cli();
  staticError = err;
  sei();
}

int8_t Corrector::periodUpdate(int16_t avgTemp)
{
  accumulatedDrift += ((int32_t)staticError) * 768;
  int8_t adj = 0;
  while (accumulatedDrift > MILLION)
  {
    accumulatedDrift -= MILLION;
    --adj;
  }
  while (accumulatedDrift < -MILLION)
  {
    accumulatedDrift += MILLION;
    ++adj;
  }
  return adj;
}
