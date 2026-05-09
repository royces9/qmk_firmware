#pragma once

#include "hardware/gpio.h"

#define TX_PIN 14
#define RX_PIN 8
#define EN_PIN 5

void init_pins(void);
void init_adb(void);
