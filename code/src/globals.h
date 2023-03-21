#ifndef GLOBALS_H
#define GLOBALS_H

#include "OSO_LCD.h"
#include "lib/time.h"

#define PERIOD_SECONDS 600
#define LONG_PRESS_TICKS 44
#define REPEAT_TICKS 8
#define BLINK_PERIOD 20
#define TIMEOUT_SECONDS 60
#define TIMEOUT_TICKS 50 * TIMEOUT_SECONDS

extern OSO_LCD lcd;
extern Time time;
extern Time prevTime;
extern uint32_t lastAdjustedAt;
extern volatile uint32_t totalSeconds;
extern volatile int16_t periodStartTemp; // Temperature C * 20
extern volatile int16_t latestMeasuredTemp; // Temperature C * 20
extern volatile bool faceNeedsQuickTick;
extern volatile uint16_t counter0;

// 0x01: conversion requested; 0x02: conversion in progress
extern volatile uint8_t dsState;

// When Timer 2 compare interrupt next runs, it will adjust counter by this many beats
// Used to fine-tune time in 1/32 second increments from UI
// Used to shorten/lengthen second for frequency correction
extern volatile uint8_t timer2Adjust;

// Returns copy to totalSeconds from within no-interrupt guard
uint32_t safeGetTotalSeconds();

//#define LED_PIN 3
#define LED_PIN 9
#define BTN_MODE_PIN 14
#define BTN_PLUS_PIN 17
#define BTN_MINUS_PIN 16

#endif
