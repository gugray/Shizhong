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

// When Timer 2 compare interrupt next runs, it will adjust counter by this much * 4
// Used to fine-tune time  in 1/32 second increments
extern volatile uint8_t timer2Adjust;

#define LED_PIN 3
#define BTN_MODE_PIN 14
#define BTN_PLUS_PIN 17
#define BTN_MINUS_PIN 16

#endif
