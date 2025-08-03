#include "uart.h"

#include "setup_pc9800_kb.h"


void init_nec9802(void) {
	//RTY
	gpio_init(RTY_PIN);
	gpio_set_dir(RTY_PIN, GPIO_OUT);
	gpio_put(RTY_PIN, 1);

	//RDY
	gpio_init(RDY_PIN);
	gpio_set_dir(RDY_PIN, GPIO_OUT);
	gpio_put(RDY_PIN, 0);

	//RST
	gpio_init(RST_PIN);
	gpio_set_dir(RST_PIN, GPIO_OUT);
	gpio_put(RST_PIN, 1);

}

void keyboard_pre_init_kb(void) {
	uart_init(BAUD_RATE);

	//init keyboard state
	init_nec9802();
}
