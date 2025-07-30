#include "hardware/gpio.h"

#include "uart.h"

#include "setup_pc9800_kb.h"
#include "pc9800_kb.h"


void init_nec9802(void) {
	/*
	//Set RTY RDY RST to outputs
	DDRD = (1<<DDD0) | (1<<DDD6) | (1<<DDD7);

	RTY_HIGH();
	RST_HIGH();
	RDY_LOW();
	*/

	//RTY
	gpio_init(RTY_PIN);
	gpio_set_dir(RTY_PIN, true);
	gpio_put(RTY_PIN, 1);

	//RDY
	gpio_init(RDY_PIN);
	gpio_set_dir(RDY_PIN, true);
	gpio_put(RDY_PIN, 1);

	//RST
	gpio_init(RST_PIN);
	gpio_set_dir(RST_PIN, true);
	gpio_put(RST_PIN, 0);

}

void keyboard_pre_init_kb(void) {
	uart_init(BAUD_RATE);

	//init keyboard state
	init_nec9802();
}

void keyboard_post_init_kb(void) {
	/*
	if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
		tap_code_delay(KC_NUM, 100);
		//tap_code(KC_NUM);
	}
	*/
	keyboard_post_init_user();
}

void keyboard_post_init_user(void) {
}
