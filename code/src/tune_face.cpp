#include <Arduino.h>
#include "tune_face.h"
#include "events.h"
#include "globals.h"
#include "persistence.h"
#include "lib/corrector.h"

// If adjustment is larger than this, calculation for delta error would overflow
#define MAX_ADJUSTMENT 687
#define MAX_ERROR 9999

// 0: finetune seconds
static uint8_t screen;
static uint8_t buf[7];
static int16_t tuneVal; // Current adjustment in 1/32 seconds
static uint16_t timeoutStart;

static uint8_t loopTune(uint16_t event);
static uint8_t loopStaticError(uint16_t event);
static uint8_t loopDeltaError(uint16_t event);
static uint8_t loopT0(uint16_t event);

static void drawTune();
static void drawErrorValue(int16_t err);
static void drawStaticError();
static void drawDeltaError();
static void drawT0();

static void resetTimeout();

static int32_t calcDeltaErr(int32_t elapsedSec);
static uint32_t safeGetTotalSeconds();

uint8_t TuneFace::loop(uint16_t event)
{
  if (ISEVENT(EVT_ENTER_FACE))
  {
    screen = 0;
    tuneVal = 0;
    drawTune();
    resetTimeout();
    return RET_STAY;
  }

  // On all screens: time out if we have no correction
  if (ISEVENT(EVT_SECOND_TICK) && tuneVal == 0 && (totalSeconds & 0xffff) - timeoutStart > TIMEOUT_SECONDS)
    return RET_HOME;

  // Events on different screens
  if (screen == 0)
    return loopTune(event);
  else if (screen == 1)
    return loopStaticError(event);
  else if (screen == 2)
    return loopDeltaError(event);
  else
    return loopT0(event);
  return RET_STAY;
}

static void resetTimeout()
{
    timeoutStart = (totalSeconds & 0xffff);
}

static uint8_t loopStaticError(uint16_t event)
{
  if (ISEVENT(EVT_BTN_MODE_LONG) || ISEVENT(EVT_BTN_MODE_SHORT))
  {
    screen = 2;
    drawDeltaError();
    resetTimeout();
    return RET_STAY;
  }
  return RET_STAY;
}

static void drawStaticError()
{
  lcd.fill(false);

  int16_t err = Corrector::getStaticError();
  lcd.buffer[2] = 0b11010011; // E
  drawErrorValue(err);

  lcd.show();
}

static uint8_t loopDeltaError(uint16_t event)
{
  if (ISEVENT(EVT_BTN_MODE_LONG) || ISEVENT(EVT_BTN_MODE_SHORT))
  {
    screen = 3;
    drawT0();
    resetTimeout();
    return RET_STAY;
  }
  if (ISEVENT(EVT_SECOND_TICK))
  {
    drawDeltaError();
  }
  if (ISEVENT(EVT_BTN_PLUS_LONG))
  {
    resetTimeout();
    // Long PLUS updates static error, and leaves tune face
    // If that's not possible, it has no effect
    uint32_t tsec = safeGetTotalSeconds();
    int32_t elapsedSec = tsec - lastAdjustedAt;
    int32_t deltaErr = calcDeltaErr(elapsedSec);
    int32_t newErr = Corrector::getStaticError() + deltaErr;
    if (lastAdjustedAt != 0 && newErr <= MAX_ERROR && newErr >= -MAX_ERROR && elapsedSec >= 6 * 60 * 60)
    {
      Corrector::setStaticError(newErr);
      Persistence::saveStaticError(newErr);
      lastAdjustedAt = tsec;
      return RET_HOME;
    }
  }
  if (ISEVENT(EVT_BTN_MINUS_LONG))
  {
    resetTimeout();
    // Long MINUS plus leaves tune face without updating static error
    // But we remember time of this adjustment
    lastAdjustedAt = safeGetTotalSeconds();
    return RET_HOME;
  }
  return RET_STAY;
}

static uint32_t safeGetTotalSeconds()
{
  uint32_t res;
  cli();
  res = totalSeconds;
  sei();
  return res;
}

static int32_t calcDeltaErr(int32_t elapsedSec)
{
  return -tuneVal * 3125000 / (elapsedSec - tuneVal / 32);
}

static void drawDeltaError()
{
  lcd.fill(false);

  lcd.buffer[2] = 0b00011111; // d

  int32_t elapsedSec = safeGetTotalSeconds() - lastAdjustedAt;
  int32_t deltaErr = calcDeltaErr(elapsedSec);
  int32_t newErr = Corrector::getStaticError() + deltaErr;
  // Less than 6h elapsed, or delta would yeet us beyond maximum error
  // Or first time adjusting
  if (lastAdjustedAt == 0 || newErr > MAX_ERROR || newErr < -MAX_ERROR || elapsedSec < 6 * 60 * 60)
  {
    lcd.buffer[4] = 0b00000010;
    lcd.buffer[5] = 0b00000010 | OSO_SYMBOL_DOT;
    lcd.buffer[6] = 0b00000010;
  }
  else
    drawErrorValue(deltaErr);

  lcd.show();
}

static void drawErrorValue(int16_t err)
{
  if (err < 0)
  {
    lcd.buffer[2] |= OSO_SYMBOL_DOT;
    err = -err;
  }
  lcd.buffer[6] = digits[err % 10];
  err /= 10;
  lcd.buffer[5] = digits[err % 10] | OSO_SYMBOL_DOT;
  err /= 10;
  lcd.buffer[4] = digits[err % 10];
  err /= 10;
  if (err != 0)
    lcd.buffer[3] = digits[err % 10];
}

static uint8_t loopT0(uint16_t event)
{
  if (ISEVENT(EVT_BTN_MODE_LONG) || ISEVENT(EVT_BTN_MODE_SHORT))
  {
    screen = 0;
    drawTune();
    return RET_STAY;
  }
  if (ISEVENT(EVT_BTN_PLUS_DOWN) || ISEVENT(EVT_BTN_MINUS_DOWN))
  {
    int16_t t = Corrector::getCrystalT0();
    if (ISEVENT(EVT_BTN_PLUS_DOWN))
      t += 2;
    else
      t -= 2;
    Corrector::setCrystalT0(t);
    Persistence::saveCrystalT0(t);
    drawT0();
    resetTimeout();
  }
  return RET_STAY;
}

static void drawT0()
{
  drawTemperature(Corrector::getCrystalT0());
}

static uint8_t loopTune(uint16_t event)
{
  if (tuneVal == 0 && ISEVENT(EVT_BTN_MODE_SHORT))
    return RET_NEXT;

  if (ISEVENT(EVT_BTN_MODE_LONG) || (tuneVal != 0 && ISEVENT(EVT_BTN_MODE_SHORT)))
  {
    screen = 1;
    drawStaticError();
    return RET_STAY;
  }

  if (ISEVENT(EVT_SECOND_TICK))
    drawTune();
  // Everything that's not a tick is user action: reset timeout counter
  else
    timeoutStart = (totalSeconds & 0xffff);

  int8_t tnDiff = 0;
  if (ISEVENT(EVT_BTN_MINUS_DOWN) || ISEVENT(EVT_BTN_MINUS_REPEAT))
    tnDiff -= 1;
  if (ISEVENT(EVT_BTN_PLUS_DOWN) || ISEVENT(EVT_BTN_PLUS_REPEAT))
    tnDiff += 1;
  if (tnDiff != 0 && tuneVal + tnDiff >= -MAX_ADJUSTMENT && tuneVal + tnDiff <= MAX_ADJUSTMENT)
  {
    tuneVal += tnDiff;
    cli();
    timer2Adjust += tnDiff * 4;
    sei();
    drawTune();
  }
  return RET_STAY;
}

static void drawTune()
{
  // "Draw" into new buffer
  memset(buf, 0, 7);

  // Current second
  buf[4] = digits[0];
  buf[5] = digits[time.sec / 10] | OSO_SYMBOL_DOT;
  buf[6] = digits[time.sec % 10];

  // Current adjustment value
  uint16_t tn = tuneVal;
  if (tuneVal < 0)
  {
    buf[2] |= OSO_SYMBOL_DOT; // Minus sign is "dot" before first digit
    tn = -tuneVal;
  }
  if (tn >= 100)
    buf[2] |= digits[tn / 100];
  if (tn >= 10)
  {
    if (tn >= 100)
      tn = tn - 100 * (tn / 100);
    buf[3] = digits[tn / 10];
  }
  buf[4] = digits[tn % 10];

  // Flush if different
  if (memcmp(buf, lcd.buffer, 7) != 0)
  {
    memcpy(lcd.buffer, buf, 7);
    lcd.show();
  }
}
