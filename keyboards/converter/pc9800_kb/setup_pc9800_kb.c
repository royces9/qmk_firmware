#include "uart.h"

#include "setup_pc9800_kb.h"

void init_nec9802(void) {
	//Set RTY RDY RST to outputs
	DDRD = (1<<DDD0) | (1<<DDD6) | (1<<DDD7);

	RTY_HIGH();
	RST_HIGH();
	RDY_LOW();
}

void keyboard_pre_init_kb(void) {
	uart_init(BAUD_RATE);

	//init keyboard state
	init_nec9802();
}
