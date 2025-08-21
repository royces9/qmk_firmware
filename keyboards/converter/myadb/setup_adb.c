#include "hardware/timer.h"

void init_adb(void) {
	//set data pin low for >3ms
	data_low(); //not implemented yet
	busy_wait_ms(3);

	//set data pin back high
	data_high();

	//wait 1s for device to ready???
	busy_wait_ms(1000);
	
}

void keyboard_pre_init_kb(void) {
	init_adb();
}
