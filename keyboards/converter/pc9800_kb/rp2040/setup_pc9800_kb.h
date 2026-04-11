#pragma once

#include "hardware/gpio.h"

#define BAUD_RATE 19200

#define RTY_PIN 8
#define RDY_PIN 14
#define RST_PIN 15

#define IS_MAKE(byte) (~(byte) & 0x80)

void init_nec9802(void);
void keyboard_pre_init_kb(void);
