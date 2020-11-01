#pragma once

#if __has_include("config.h")
#include "config.h"
#endif

#ifndef I2C_ADDRESS
#define I2C_ADDRESS 0x30
#endif

#ifndef JOYSTICK_X_PIN
#define JOYSTICK_X_PIN A0
#endif

#ifndef JOYSTICK_Y_PIN
#define JOYSTICK_Y_PIN A1
#endif

#ifndef LED_JOYSTICK_PIN
#define LED_JOYSTICK_PIN 5
#endif