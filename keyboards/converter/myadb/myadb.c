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
	uint8_t send = 0x01;
	send |= (address << 4);

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void cmd_listen(uint8_t address, uint8_t reg) {
	uint8_t send = 0x08;
	send |= (address << 4);
	send |= (reg & 0x03);

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void cmd_talk(uint8_t address, uint8_t reg) {
	uint8_t send = 0x0C;
	send |= (address << 4);
	send |= (reg & 0x03);

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
	gpio_put(TX_PIN, 0);
	busy_wait_us_32(time);
}

void set_high(uint32_t time) {
	gpio_put(TX_PIN, 1);
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
	uint8_t list[] = {
		0x80,
		0x40,
		0x20,
		0x10,
		0x08,
		0x04,
		0x02,
		0x01
	};

	for(int i = 0; i < 8; ++i) {
		//if logical 1
		if(list[i] & byte) {
			send_one();
		} else {
			send_zero();
		}
	}
}


#define _BYTE_SIZE (8)
uint8_t read_data(uint8_t *data) {
	uint8_t flag = 1;
	uint8_t val = 0;

	//skip the start bit
	while(!(val=gpio_get(RX_PIN)) );
	while( (val=gpio_get(RX_PIN)) );
	
	//start grabbing data
	int i = 0;
	for(i = 0; (i < (8 * _BYTE_SIZE * sizeof(*data))) && flag; ++i) {
		int data_ind1 = i / (_BYTE_SIZE * sizeof(*data));
		int data_ind2 = i % (_BYTE_SIZE * sizeof(*data));

		uint32_t start = time_us_32();
		while(!(val=gpio_get(RX_PIN)) );
		uint32_t mid = time_us_32();
		while( (val=gpio_get(RX_PIN)) ) {
			if( ((time_us_32() - mid) > 80) ) {
				flag = 0;
				break;
			}
		}

		uint32_t low_time = mid - start;
		if(low_time < 0) {
			flag = 0;
		} else if(low_time < 50) {
			data[data_ind1] |= (1 << data_ind2);
		}
	}

	//return number of bytes read
	return i / _BYTE_SIZE;
}


void enable_rx(void) {
	gpio_put(EN_PIN, 1);
}

void disable_rx(void) {
	gpio_put(EN_PIN, 0);
}


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
