#pragma once

#include <stdint.h>
#include <stdbool.h>
#include QMK_KEYBOARD_H

enum custom_keycodes {
	MYCAPS=SAFE_RANGE,
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record);
