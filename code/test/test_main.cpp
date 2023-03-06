extern "C"
{
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "unity.h"
}

#include "../src/lib/time.h"

char bufx[1024];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_overflow_diff()
{
  uint16_t valLo = 0xfffe;
  uint16_t valHi = 0x0001;
  uint16_t diff = valHi - valLo;
  TEST_ASSERT_EQUAL(3, diff);
}

void test_float_cast()
{
  uint16_t a = 10;
  uint16_t res = round(a * 1.1);
  TEST_ASSERT_EQUAL(11, res);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_overflow_diff);
  RUN_TEST(test_float_cast);
  return UNITY_END();
}
