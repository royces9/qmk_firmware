#include <stdint.h>

#include "print.h"
#include "hardware/timer.h"

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

#define BUFFER_SIZE (8)
uint8_t matrix_scan(void) {
	//static ring buffer for when keyboard returns 2 bytes
	static uint8_t input_buffer[BUFFER_SIZE] = {0};
	static uint8_t buffer_head = 0;
	static uint8_t buffer_len = 0;

	if(buffer_len) {
		uint8_t byte = input_buffer[buffer_head];
		
		uint8_t row = (byte & 0x70) >> 4;
		uint8_t column = byte & 0x0F;
				
		++buffer_head;
		buffer_head = buffer_head % BUFFER_SIZE;
		--buffer_len;

		if(byte == 0xFF) {
			return 0;
		}

		if( byte & 0x80 ) {
			matrix[row] &= ~(1U << column);
		} else {
			matrix[row] |= 1U << column;
		}
		return 1;
	}
		
	uint32_t scan_start = time_us_32();
	uint8_t out = 0;

	//keyboard default address is 2
	cmd_talk(2, 0);

	uint8_t data[8] = {0};
	enable_rx();

	uint32_t start = time_us_32();

       	while( (time_us_32() - start) < 260) {
		if( !(read_pin()) ) {
			uint8_t read = read_bytes_adb(data);
			if(read) {
				uint8_t row = (data[0] & 0x70) >> 4;
				uint8_t column = data[0] & 0x0F;
				
				if( data[0] & 0x80 ) {
					matrix[row] &= ~(1U << column);
				} else {
					matrix[row] |= 1U << column;
				}

				if(read == 2) {
					uint8_t write_ind = (buffer_head + buffer_len) % BUFFER_SIZE;
					++buffer_len;
					input_buffer[write_ind] = data[1];
				}

				out = 1;
				break;
			}
		}
	}
	disable_rx();

	matrix_scan_kb();
	
	//poll every 11ms
	while( (time_us_32() - scan_start) < 11000 );

	return out;
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
