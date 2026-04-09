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
}

uint8_t matrix_scan(void) {
	if(!uart_available()) {
		return 0;
	}

	RDY_HIGH();

	uint8_t byte = uart_getchar();
	handle_byte(byte);

	RDY_LOW();

	return 0;
}
