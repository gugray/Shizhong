#ifndef GLOBALS_H
#define GLOBALS_H

#include "OSO_LCD.h"
#include "lib/time.h"

#define LONG_PRESS_TICKS 44
#define REPEAT_TICKS 8
#define BLINK_PERIOD 20
#define TIMEOUT_SECONDS 60
#define TIMEOUT_TICKS 50 * TIMEOUT_SECONDS

extern OSO_LCD lcd;
extern Time time;
extern Time prevTime;
extern volatile bool faceNeedsQuickTick;
extern volatile uint16_t counter0;

#define LED_PIN 3
#define BTN_MODE_PIN 14
#define BTN_PLUS_PIN 16
#define BTN_MINUS_PIN 17

#endif
