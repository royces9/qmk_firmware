#include "myadb.h"

#include "hardware/timer.h"

void init_pins(void) {
	gpio_init(TX_PIN);
	gpio_set_dir(TX_PIN, GPIO_OUT);
	gpio_put(TX_PIN, 0);
	
	gpio_init(RX_PIN);
	gpio_set_dir(RX_PIN, GPIO_IN);

	gpio_init(EN_PIN);
	gpio_set_dir(EN_PIN, GPIO_OUT);
	gpio_put(EN_PIN, 0);
}

void init_adb(void) {
	init_pins();

	//set data pin low for >3ms
	set_low(0);
	busy_wait_ms(3);

	//set data pin back high
	set_high(0);

	//wait 1s for device to ready???
	busy_wait_ms(1000);
}
