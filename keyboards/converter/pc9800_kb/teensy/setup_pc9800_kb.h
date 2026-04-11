#pragma once

#include <avr/io.h>

#define BAUD_RATE 19200

//RTY on D0
//RDY on D6
//RST on D7

#define RTY_HIGH() (PORTD |= (1U << PORTD0))
#define RTY_LOW() (PORTD &= ~(1U << PORTD0))

#define RDY_HIGH() (PORTD |= (1U << PORTD6))
#define RDY_LOW() (PORTD &= ~(1U << PORTD6))

#define RST_HIGH() (PORTD |= (1U << PORTD7))
#define RST_LOW() (PORTD &= ~(1U << PORTD7))

#define IS_MAKE(byte) (~(byte) & 0x80)

void init_nec9802(void);
void keyboard_pre_init_kb(void);
void keyboard_post_init_kb(void);
