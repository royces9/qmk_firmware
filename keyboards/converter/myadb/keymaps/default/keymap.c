#include "print.h"
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT( \
		KC_A  , KC_S   , KC_D , KC_F   , KC_H  , KC_G   , KC_Z   , KC_X   , KC_C   , KC_V   , KC_NO  , KC_B   , KC_Q   , KC_W   , KC_E   , KC_R  , \
		KC_Y  , KC_T   , KC_1 , KC_2   , KC_3  , KC_4   , KC_6   , KC_5   , KC_EQL , KC_9   , KC_7   , KC_MINS, KC_8   , KC_0   , KC_RBRC, KC_O  , \
		KC_U  , KC_LBRC, KC_I , KC_P   , KC_ENT, KC_L   , KC_J   , KC_QUOT, KC_K   , KC_SCLN, KC_BSLS, KC_COMM, KC_SLSH, KC_N   , KC_M   , KC_DOT, \
		KC_TAB, KC_SPC , KC_NO, KC_BSPC, KC_NO , KC_ESC , KC_LCTL, KC_LWIN, KC_LSFT, KC_LCAP, KC_LALT, KC_LEFT, KC_RGHT, KC_DOWN, KC_UP  , KC_NO , \
		KC_NO , KC_PDOT, KC_NO, KC_PAST, KC_NO , KC_PPLS, KC_NO  , KC_BSPC, KC_NO  , KC_NO  , KC_NO  , KC_PSLS, KC_PENT, KC_NO  , KC_PMNS, KC_NO , \
		KC_NO , KC_PEQL, KC_P0, KC_P1  , KC_P2 , KC_P3  , KC_P4  , KC_P5  , KC_P6  , KC_P7  , KC_NO  , KC_P8  , KC_P9  , KC_NO  , KC_NO  , KC_NO \
		),
};
