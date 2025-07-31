#include QMK_KEYBOARD_H

#include "keymap_japanese.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT( \
		KC_ESC , JP_Q   , JP_F   , JP_COMM   , KC_MINUS, KC_NO  , KC_NO, KC_LEFT_SHIFT, \
		JP_1   , JP_W   , JP_G   , JP_DOT    , KC_SLASH, KC_NO  , KC_NO, KC_CAPS      , \
		JP_2   , JP_E   , JP_H   , JP_SLSH   , KC_KP_7 , KC_F11 , KC_F1, JP_KANA      , \
		JP_3   , JP_R   , JP_J   , JP_MINS   , KC_KP_8 , KC_F12 , KC_F2, KC_NO        , \
		JP_4   , JP_T   , JP_K   , KC_SPC    , KC_KP_9 , KC_F13 , KC_F3, KC_LEFT_CTRL , \
		JP_5   , JP_Y   , JP_L   , KC_NO     , KC_ASTR , KC_F14 , KC_F4,		\
		JP_6   , JP_U   , JP_SCLN, KC_PGUP   , KC_KP_4 , KC_F15 , KC_F5, \
		JP_7   , JP_I   , JP_COLN, KC_PGDN   , KC_KP_5 , KC_F6  , \
		JP_8   , JP_O   , JP_RBRC, KC_INS    , KC_KP_6 , KC_F7  , \
		JP_9   , JP_P   , JP_Z   , KC_DEL    , KC_PLUS , KC_F8  , \
		JP_0   , JP_AT  , JP_X   , KC_UP     , KC_KP_1 , KC_F9  , \
		JP_MINS, JP_LBRC, JP_C   , KC_LEFT   , KC_KP_2 , KC_F10 , \
		JP_CIRC, KC_ENT , JP_V   , KC_RGHT   , KC_KP_3 , \
		JP_YEN , JP_A   , JP_B   , KC_DOWN   , KC_PEQL , \
		KC_BSPC, JP_S   , JP_N   , KC_NUM_LOCK, KC_KP_0 , KC_HOME, \
		KC_TAB , JP_D   , JP_M   , KC_HELP   , KC_PCMM
	       ),
};
