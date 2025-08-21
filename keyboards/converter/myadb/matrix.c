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
}

uint8_t handle_byte(void) {
	uint8_t out = 0;
	for(int i = 0; i < 8; ++i) {
		uint8_t cond = true;
		uint32_t start = time_us_32();
		uint8_t val = 0;
		do {
			val = gpio_get();
		} while (!val);

		val = 1;
		uint32_t mid = time_us_32();

		do {
			val = gpio_get();
		} while (val);

		uint32_t end = time_us_32();
		
		uint32_t head = mid - start;
		uint32_t tail = end - mid;

		uint8_t bit = 0;
		if( head < tail) {
			bit = 1;
		}
		
		out |= bit << i;
	}
	
	return out;
}

uint8_t matrix_scan(void) {
	//pull data low for 800us
	data_low(); //not implemented yet
	busy_wait_us(800);

	//pull data back high for 70us
	data_high();
	busy_wait_us(800);

	uint8_t byte = handle_byte();

	
	return 0;
}
