#include "setup_adb.h"
#include "myadb.h"

#include "hardware/gpio.h"
#include "hardware/timer.h"

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
	send |= ((address << 4) & (reg & 0x03));

	sig_attn();
	sig_sync();
	send_byte_adb(send);
	send_stop();
}

void cmd_talk(uint8_t address, uint8_t reg) {
	uint8_t send = 0x0C;
	send |= ((address << 4) & (reg & 0x03));

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
		//if logical 0
		if(list[i] & byte) {
			send_zero();
		} else {
			send_one();
		}
	}
}


void read_data(uint8_t *data) {
	uint8_t flag = 0;
	uint8_t val = 0;

	//skip the start bit
	while(!(val=gpio_get(RX_PIN)));
	while(val=gpio_get(RX_PIN));
	
	//start grabbing data
	uint8_t flag = 0;

	uint16_t low_count = 0;
	uint16_t high_count = 0;

	uint8_t data_ind1 = 0;
	uint8_t data_ind2 = 0;

	for(int i = 0; i < 8 || flag; ++i) {
		for(int j = 0; j < 8; ++j) {
			while(!(val=gpio_get(RX_PIN))) {
				++low_count;
				busy_wait_us_32(1);
			}
			while(val=gpio_get(RX_PIN)) {
				++high_count;
				if(high_count > 100) {
					flag = 1
						break;
				}
				busy_wait_us_32(1);
			}
			if(low_count < high_count) {
				data[i] |= (1 << j);
				//data[data_ind1] |= (1 << data_ind2);
			}
		}
	}
}

uint8_t handle_byte(void) {
	enable_rx();
	uint8_t out = 0;
	for(int i = 0; i < 8; ++i) {
                //uint8_t cond = true;
                uint32_t start = time_us_32();
                uint8_t val = 0;
                do {
                        val = gpio_get(RX_PIN);
                } while (!val);

                val = 1;
                uint32_t mid = time_us_32();

                do {
                        val = gpio_get(RX_PIN);
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

	disable_rx();
        return out;
}

void enable_rx(void) {
	gpio_put(EN_PIN, 1);
}

void disable_rx(void) {
	gpio_put(EN_PIN, 0);
}
