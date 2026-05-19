#pragma once

#include <stdint.h>
#include "hardware/gpio.h"

#define TX_PIN 14
#define RX_PIN 8
#define EN_PIN 5

void cmd_sendreset(uint8_t address, uint8_t reg);
void cmd_flush(uint8_t address, uint8_t reg);
void cmd_listen(uint8_t address, uint8_t reg);
void cmd_talk(uint8_t address, uint8_t reg);

void sig_attn(void);
void sig_sync(void);
void sig_global_reset(void);
void sig_service_request(void);

void send_stop(void);

void set_low(uint32_t time);
void set_high(uint32_t time);

void send_zero(void);
void send_one(void);

void send_byte_adb(uint8_t byte);
uint8_t read_data(uint64_t *data);

void enable_rx(void);
void disable_rx(void);


//setup
void init_pins(void);
void init_adb(void);

void keyboard_pre_init_kb(void);
