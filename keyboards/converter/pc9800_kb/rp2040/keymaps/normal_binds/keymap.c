#include QMK_KEYBOARD_H

#include "keymap_japanese.h"

//MYCAPS set in process_record_kb set in pc9800_kb.c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT( \
		KC_ESC , KC_Q   , KC_F   , KC_COMM, KC_MINUS, KC_PDOT, KC_NO, KC_LSFT, \
		KC_1   , KC_W   , KC_G   , KC_DOT , KC_SLASH, KC_LWIN, KC_NO, MYCAPS, \
		KC_2   , KC_E   , KC_H   , KC_SLSH, KC_KP_7 , KC_F11 , KC_F1, JP_KANA, \
		KC_3   , KC_R   , KC_J   , KC_MINS, KC_KP_8 , KC_F12 , KC_F2, KC_LALT, \
		KC_4   , KC_T   , KC_K   , KC_SPC , KC_KP_9 , KC_F13 , KC_F3, KC_LCTL, \
		KC_5   , KC_Y   , KC_L   , KC_RWIN, KC_ASTR , KC_F14 , KC_F4, \
		KC_6   , KC_U   , KC_SCLN, KC_PGUP, KC_KP_4 , KC_F15 , KC_F5, \
		KC_7   , KC_I   , KC_QUOT, KC_PGDN, KC_KP_5 , KC_F6  , \
		KC_8   , KC_O   , KC_RBRC, KC_INS , KC_KP_6 , KC_F7  , \
		KC_9   , KC_P   , KC_Z   , KC_DEL , KC_PLUS , KC_F8  , \
		KC_0   , KC_AT  , KC_X   , KC_UP  , KC_KP_1 , KC_F9  , \
		KC_MINS, KC_LBRC, KC_C   , KC_LEFT, KC_KP_2 , KC_F10 , \
		KC_CIRC, KC_ENT , KC_V   , KC_RGHT, KC_KP_3 , \
		KC_BSLS, KC_A   , KC_B   , KC_DOWN, KC_PEQL , \
		KC_BSPC, KC_S   , KC_N   , KC_NUM , KC_KP_0 , KC_HOME, \
		KC_TAB , KC_D   , KC_M   , KC_HELP, KC_PCMM
	       ),
};
