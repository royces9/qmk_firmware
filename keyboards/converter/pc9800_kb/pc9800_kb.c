#include QMK_KEYBOARD_H

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
	case MYCAPS:
		tap_code(KC_CAPS);
		break;
	}
	process_record_user(keycode, record);
	return true;
}
