#pragma once

#include <avr/io.h>
#include "uart.h"

#define BAUD_RATE 19200

//RTY on D0
//RDY on D6
//RST on D7

void __attribute__ ((optimize("O0"))) RTY_high(void);
void __attribute__ ((optimize("O0"))) RTY_low(void);

void __attribute__ ((optimize("O0"))) RDY_high(void);
void __attribute__ ((optimize("O0"))) RDY_low(void);

void __attribute__ ((optimize("O0"))) RST_high(void);
void __attribute__ ((optimize("O0"))) RST_low(void);

void init_nec9802(void);
void keyboard_pre_init_kb(void);

void matrix_scan_kb(void);
