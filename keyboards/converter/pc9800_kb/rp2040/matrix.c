#include <stdint.h>

#include "hardware/timer.h"
#include "uart.h"
#include "matrix.h"
#include "setup_pc9800_kb.h"

#include QMK_KEYBOARD_H

static matrix_row_t matrix[MATRIX_ROWS];

void handle_byte(uint8_t byte) {

	//get bottom 4 bits
	uint8_t row = byte & 0x0F;

	//get next 3 bits
	uint8_t column = (byte & 0x70) >> 4;

	if(IS_MAKE(byte)) {
		matrix[row] |= (1U << column);
	} else {
		matrix[row] &= ~(1U << column);
	}
}

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
	if(!uart_available()) {
		return 0;
	}

	//RDY_HIGH();
	gpio_put(RDY_PIN, 1);

	uint8_t byte = uart_read();
	handle_byte(byte);

	//wait 4us
	busy_wait_us_32(4);

	gpio_put(RDY_PIN, 0);

	matrix_scan_kb();

	return 1;
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
