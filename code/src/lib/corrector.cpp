#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "corrector.h"

#define HUNDRED_MILLION 100000000

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
  while (accumulatedDrift > HUNDRED_MILLION)
  {
    accumulatedDrift -= HUNDRED_MILLION;
    --adj;
  }
  while (accumulatedDrift < -HUNDRED_MILLION)
  {
    accumulatedDrift += HUNDRED_MILLION;
    ++adj;
  }
  return adj;
}
