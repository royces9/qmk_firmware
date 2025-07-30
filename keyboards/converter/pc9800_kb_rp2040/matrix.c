#include <stdint.h>

#include "uart.h"
#include "matrix.h"
#include "setup_pc9800_kb.h"

#include "print.h"

static matrix_row_t matrix[MATRIX_ROWS];

//idk why but this is necessary
void __attribute__ ((optimize("O0"))) handle_byte(uint8_t byte) {
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

matrix_row_t  matrix_get_row(uint8_t row) {
	return matrix[row];
}

void matrix_print(void) {
}


void matrix_init(void) {
	for(int i = 0; i < MATRIX_ROWS; ++i) {
		matrix[i] = 0;
	}
	
	matrix_init_quantum();
}

uint8_t matrix_scan(void) {
	if(!uart_available()) {
		return 0;
	}

	//RDY_HIGH();
	gpio_put(RDY_PIN, 1);

	uint8_t byte = uart_getchar();
	handle_byte(byte);

	//RDY_LOW();
	gpio_put(RDY_PIN, 0);

	matrix_scan_quantum();
	return 0;
}

__attribute__ ((weak)) void matrix_init_kb(void) {
	matrix_init_user();
}

__attribute__ ((weak)) void matrix_scan_kb(void) {
	matrix_scan_user();
}

__attribute__ ((weak)) void matrix_init_user(void) {
}

__attribute__ ((weak)) void matrix_scan_user(void) {
}
