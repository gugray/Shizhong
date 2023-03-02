extern "C"
{
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

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_overflow_diff);
  return UNITY_END();
}
