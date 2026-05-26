#pragma once

#include "uart.h"

#define BAUD_RATE 19200

#define RTY_PIN 8
#define RDY_PIN 14
#define RST_PIN 15

void RDY_high(void);
void RDY_low(void);

void init_nec9802(void);
void keyboard_pre_init_kb(void);
