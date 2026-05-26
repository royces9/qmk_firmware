#include "uart.h"

#include "setup_pc9800_kb.h"

void __attribute__ ((optimize("O0"))) RTY_high(void) {
	(PORTD |= (1U << PORTD0));
}

void __attribute__ ((optimize("O0"))) RTY_low(void) {
	(PORTD &= ~(1U << PORTD0));
}

void __attribute__ ((optimize("O0"))) RDY_high(void) {
	(PORTD |= (1U << PORTD6));
}

void __attribute__ ((optimize("O0"))) RDY_low(void) {
	(PORTD &= ~(1U << PORTD6));
}

void __attribute__ ((optimize("O0"))) RST_high(void) {
	(PORTD |= (1U << PORTD7));
}

void __attribute__ ((optimize("O0"))) RST_low(void) {
	(PORTD &= ~(1U << PORTD7));
}

void init_nec9802(void) {
	//Set RTY RDY RST to outputs
	DDRD = (1<<DDD0) | (1<<DDD6) | (1<<DDD7);

	RTY_high();
	RST_high();
	RDY_low();
}

void keyboard_pre_init_kb(void) {
	uart_init(BAUD_RATE);

	//init keyboard state
	init_nec9802();
}
