#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#endif

#include "corrector.h"

#define CRYSTAL_K -0.035
#define CRYSTAL_K_192 -6.72
#define MILLION 1000000

static int16_t staticError = 0;
static int32_t accumulatedDrift = 0;
static int16_t crystalT0 = 500; // C * 20

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

int16_t Corrector::getCrystalT0()
{
  return crystalT0;
}

void Corrector::setCrystalT0(int16_t t0)
{
  cli();
  crystalT0 = t0;
  sei();
}

int8_t Corrector::periodUpdate(int16_t avgTemp)
{
  // Dynamic drift in this period
  // float dT = (crystalT0 - avgTemp) / 20.0F;
  // float dynError = CRYSTAL_K * dT * dT * 100.0F; // Error is PPM * 100 for our formulas
  // int32_t dynDrift = round(dynError * 768.0F);

  int32_t a = (crystalT0 - avgTemp);
  a *= a;
  int32_t dynDrift = round(a * CRYSTAL_K_192);

  accumulatedDrift += ((int32_t)staticError) * 768 + dynDrift;

  // Returned value must be at least +-2; we can't magick with a single beat in a second
  if (accumulatedDrift < 2 * MILLION && accumulatedDrift > -2 * MILLION)
    return 0;

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
