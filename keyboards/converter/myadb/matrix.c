#include <stdint.h>

#include "hardware/timer.h"
#include "matrix.h"

#include QMK_KEYBOARD_H

static matrix_row_t matrix[MATRIX_ROWS];

void matrix_print(void) {
}

matrix_row_t matrix_get_row(uint8_t row) {
	return matrix[row];
}

void matrix_init(void) {
	for(int i = 0; i < MATRIX_ROWS; ++i) {
		matrix[i] = 0;
	}

	matrix_init_kb();
}

uint8_t matrix_scan(void) {
	uint8_t data[10] = {0};

	sig_attn();
	sig_sync();

	//keyboard default address is 2
	cmd_talk(2, 0);

	uint32_t start = time_us_32();
	uint8_t val = 1;

	enable_rx();

	while( (time_us_32() - start) < 260 ) {
		val = gpio_get(RX_PIN);
		if(!val) {
			read_data(data);
		}
	}
	
	
	return 0;
}

__attribute__((weak)) void matrix_init_kb(void) {
	matrix_init_user();
}

__attribute__((weak)) void matrix_scan_kb(void) {
	matrix_scan_user();
}

__attribute__((weak)) void matrix_init_user(void) {
}

__attribute__((weak)) void matrix_scan_user(void) {
}
