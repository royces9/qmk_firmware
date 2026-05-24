#include "myadb.h"

#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "print.h"

void cmd_sendreset(uint8_t address, uint8_t reg) {
	sig_attn();
	sig_sync();
	send_byte_adb(0x00);
	send_stop();
}

void cmd_flush(uint8_t address, uint8_t reg) {
	uint8_t send = 0x01 | (address << 4);

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void cmd_listen(uint8_t address, uint8_t reg) {
	uint8_t send = 0x08 | (address << 4) | (reg & 0x03);

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void cmd_talk(uint8_t address, uint8_t reg) {
	uint8_t send = 0x0C | (address << 4) | (reg & 0x03);

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void sig_attn(void) {
	//Attention
	set_low(800);
}

void sig_sync(void) {
	//Sync
	set_high(65);
}

void sig_global_reset(void) {
	//wait 3.2ms
	set_low(200);
	busy_wait_ms(3);

	set_high(0);
}

void sig_service_request(void) {
	//empty for now...
}



void send_stop(void) {
	set_low(70);
	set_high(0);
}

void set_low(uint32_t time) {
	gpio_put(DATA_PIN, 0);	
	busy_wait_us_32(time);
}

void set_high(uint32_t time) {
	gpio_put(DATA_PIN, 1);
	busy_wait_us_32(time);
}


void send_zero(void) {
	set_low(65);
	set_high(35);
}

void send_one(void) {
	set_low(35);
	set_high(65);
}

void send_byte_adb(uint8_t byte) {
	for(int i = 0; i < 8; ++i) {
		//if logical 1
		if( (0x80 >> i) & byte) {
			send_one();
		} else {
			send_zero();
		}
	}
}


#define _BYTE_SIZE (8)
uint8_t read_bytes_adb(uint8_t *data) {
	while(!(read_pin()) );
	while( (read_pin()) );
	
	//start grabbing data
	int i = 0;
	for(uint8_t flag = 1; (i < (8 * _BYTE_SIZE * sizeof(*data))) && flag; ++i) {
		uint32_t start = time_us_32();
		while(!(read_pin()) );

		uint32_t mid = time_us_32();

		while( (read_pin()) ) {
			if( ((time_us_32() - mid) > 80) ) {
				flag = 0;
				break;
			}
		}

		uint32_t low_time = mid - start;
		if(low_time < 0) {
			flag = 0;
		} else if(low_time < 50) {
			int data_ind1 = i / (_BYTE_SIZE * sizeof(*data));
			int data_ind2 = i % (_BYTE_SIZE * sizeof(*data));
			data[data_ind1] |= (0x80 >> data_ind2);
		}
	}

	//return number of bytes read
	return i / _BYTE_SIZE;
}


uint8_t read_pin(void) {
	return gpio_get(DATA_PIN);
}

void enable_rx(void) {
	gpio_set_dir(DATA_PIN, GPIO_IN);
}

void disable_rx(void) {
	gpio_set_dir(DATA_PIN, GPIO_OUT);
}


void init_pins(void) {
        gpio_init(DATA_PIN);
        gpio_set_dir(DATA_PIN, GPIO_OUT);
        gpio_put(DATA_PIN, 0);
}


void init_adb(void) {
        init_pins();

        //set data pin low for >3ms
	set_low(0);
        busy_wait_ms(4);

        //set data pin back high
	set_high(0);


        //wait 1s for device to ready??
	busy_wait_ms(1000);

	/*
	//send command to disable service request to device
	cmd_listen(2, 3);
	busy_wait_us_32(200);

	send_one();
	send_byte_adb(0x00);
	send_byte_adb(0x42);
	send_zero();
	*/
}

void keyboard_pre_init_kb(void) {
        init_adb();
}
