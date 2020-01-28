#include QMK_KEYBOARD_H
#include "version.h"

#define _____ KC_TRNS
#define __x__ KC_NO

enum layer_codes {
      BASE = 0,                 /* Default layer */
      XWINDOW,
      EMACS,
      EMACS2,
      NUMERIC,
      NUM_UP,                   /* Shifted numeric symbols */
      SYMBOLS,
      SYMBOLS2,
      MDIA,      
      BLANK
};

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  SHRINK_WINDOW,                /* Emacs, shrink-window-horizontally */
  ENLARGE_WINDOW,               /* Emacs, enlarge-window-horizontally */      
};

enum combo_events {
    STUMP_EXEC,
    STUMP_TOGGLE,
    COMBO_SEND_ESC,
};

const uint16_t PROGMEM stump_exec_combo[]     = {KC_LEFT, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM stump_toggle_combo[]   = {KC_UP,   KC_DOWN,  COMBO_END};
const uint16_t PROGMEM combo_send_esc_combo[] = {KC_BSPC, KC_TAB,   COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [STUMP_EXEC] = COMBO_ACTION(stump_exec_combo),
    [STUMP_TOGGLE] = COMBO_ACTION(stump_toggle_combo),
    [COMBO_SEND_ESC] = COMBO_ACTION(combo_send_esc_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
  case STUMP_EXEC:
      if (pressed) {
          SEND_STRING(SS_LCTRL("t") SS_LSFT("!"));
        /* tap_code16(LCTL(KC_C)); */
      }
      break;
  case COMBO_SEND_ESC:
      if (pressed) {
          SEND_STRING(SS_TAP(X_ESC));
      }
      break;

  case STUMP_TOGGLE:
      if (pressed) {
          SEND_STRING(SS_LCTRL("t") SS_LCTRL("t"));
      }
      break;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                                                              
[BASE] = LAYOUT_ergodox(
  LCTL(KC_F1),   KC_VOLD, KC_VOLU,        __x__,       __x__,         KC_F6, RESET,
  __x__,         __x__,   KC_W,           KC_E,        KC_R,          KC_T,  __x__,
  __x__,         KC_A,    WIN_T(KC_S),    ALT_T(KC_D), CTL_T(KC_F),   KC_G,
  OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,  KC_V, KC_B,  __x__,
  TG(EMACS),     __x__,   __x__,   __x__, __x__,
                                                                     __x__,  __x__,
                                                                             __x__,
                                       LT(XWINDOW, KC_BSPC), CTL_T(KC_SPC), KC_TAB,

  __x__, __x__,            __x__,             __x__,             __x__,          __x__,  __x__,
  __x__, LT(NUM_UP, KC_Y), LT(NUMERIC, KC_U), LT(SYMBOLS, KC_I), KC_O,           __x__,  __x__,
  KC_H,  CTL_T(KC_J),      ALT_T(KC_K),       WIN_T(KC_L),       KC_P, TG(MDIA),
  __x__, KC_N,             KC_M,              KC_COMMA,          KC_DOT,         KC_Q,   OSM(MOD_RSFT),
                           __x__,             __x__,             __x__,          __x__,  __x__,
  __x__, __x__,
  __x__,
  LT(MDIA, KC_ESC), LT(EMACS, KC_ENT), __x__),



[XWINDOW] = LAYOUT_ergodox(
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____, _____, 
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____,
                                      _____, _____,
                                             _____,
                               _____, _____, _____,
                                      
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, KC_F4, KC_F3, KC_F5, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, KC_F1, KC_F2
),



[EMACS] = LAYOUT_ergodox(
  _____, _____,   _____,   _____,   _____,   _____,   _____,
  _____, _____,   _____,   C(KC_P), A(KC_V), _____,   _____,
  _____, C(KC_A), C(KC_B), C(KC_N), C(KC_F), C(KC_E),
  _____, _____,   _____,   _____,   C(KC_V), _____,   _____,
  _____, _____,   _____,   _____,   _____,
                                                   _____, _____,
                                                          _____,
                             C(S(KC_SPC)), LCA(KC_SPACE), _____,
  
  _____, _____,  ENLARGE_WINDOW, _____, SHRINK_WINDOW, _____, _____,
  _____, _____,  _____,          _____, _____,         _____, _____,
         _____,  _____,          _____, _____,         _____, _____,  
  _____, _____,  _____,          _____, _____,         _____, _____,
                 _____,          _____, _____,         _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),



[EMACS2] = LAYOUT_ergodox(
  _____, _____, _____,   _____,   _____,   _____, _____,
  _____, _____, _____,   A(KC_P), _____,   _____, _____,
  _____, _____, A(KC_B), A(KC_N), A(KC_F), _____, 
  _____, _____, _____,   _____,   _____,   _____, _____,
  _____, _____, _____,   _____,   _____,
                                           _____, _____,
                                                  _____,
                                    _____, _____, _____,
                                      
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, _____, _____
),


   
[NUMERIC] = LAYOUT_ergodox(
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, KC_1,  KC_2,  KC_3,  _____, _____,
  _____, KC_0,  KC_4,  KC_5,  KC_6,  _____,
  _____, KC_0,  KC_7,  KC_8,  KC_9,  _____, _____,
  _____, _____, _____, _____, _____,
                                     _____, _____,
                                            _____,
                              _____, _____, _____,
                                      
  _____, _____, _____, _____,  _____,  _____, _____,
  _____, _____, _____, _____,  _____,  _____, _____,
         _____, _____, _____,  _____,  _____, _____,
  _____, _____, _____, _____,  _____,  _____, _____,
                _____, _____,  _____,  _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),



[NUM_UP] = LAYOUT_ergodox(
  _____, _____,       _____,        _____,       _____,         _____, _____,
  _____, _____,       KC_EXCLAIM,   KC_AT,       KC_HASH,       _____, _____,
  _____, KC_QUESTION, KC_DOLLAR,    KC_PERCENT,  KC_CIRCUMFLEX, _____,
  _____, _____,       KC_AMPERSAND, KC_ASTERISK, _____,         _____, _____,
  _____, _____,       _____,        _____,       _____,
                                                                _____, _____,
                                                                       _____,
                                                         _____, _____, _____,
                                      
  _____, _____, _____, _____,  _____,  _____, _____,
  _____, _____, _____, _____,  _____,  _____, _____,
         _____, _____, _____,  _____,  _____, _____,
  _____, _____, _____, _____,  _____,  _____, _____,
                _____, _____,  _____,  _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),



[SYMBOLS] = LAYOUT_ergodox(
  _____, _____, KC_LBRC, KC_RBRC,  KC_LCBR,  KC_RCBR,  _____,
  _____, _____, _____,   KC_DQUO,  KC_LPRN,  KC_RPRN,  _____,
  _____, _____, _____,   KC_QUOTE, KC_MINUS, KC_GRAVE, 
  _____, _____, _____,   KC_EQUAL, KC_PLUS,  KC_UNDS,  _____,
  _____, _____, _____,   KC_LABK,  KC_RABK,
                                             _____, _____,
                                                    _____,
                                      _____, _____, _____,
                                      
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),



[SYMBOLS2] = LAYOUT_ergodox(
  _____, _____, _____,   _____, _____, _____,    _____,
  _____, _____, KC_PIPE, _____, _____, _____,    _____,
  _____, _____, _____,   _____, _____, _____,
  _____, _____, _____,   _____, _____, KC_TILDE, _____,
  _____, _____, _____,   _____,        _____,
                                          _____, _____,
                                                 _____,
                                   _____, _____, _____,
                                      
  _____, _____, _____,    _____,     _____, _____,     _____,
  _____, _____, KC_COLON, KC_SCOLON, _____, _____,     _____,
         _____, _____,    _____,     _____, _____,     _____,
  _____, _____, KC_SLASH, _____,     _____, KC_BSLASH, _____,
                _____,    _____,     _____, _____,     _____,
  _____, _____,
  _____,
  _____, _____, _____
),



[MDIA] = LAYOUT_ergodox(
  _____, KC_ACL0, KC_ACL1, KC_ACL2, _____,   _____, _____,
  _____, _____,   KC_WH_L, KC_MS_U, KC_WH_U, _____, _____,
  _____, _____,   KC_MS_L, KC_MS_D, KC_MS_R, _____,
  _____, _____,   _____,   _____,   KC_WH_D, _____, _____,
  _____, _____,   _____,   _____,   _____,
                                           RGB_TOG, _____,
                                                    _____,
                                  KC_BTN2, KC_BTN1, KC_BTN3,

  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),  



/* Used for copy/paste for new layers. */
[BLANK] = LAYOUT_ergodox(
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, 
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____,
                                     _____, _____,
                                            _____,
                              _____, _____, _____,
                                      
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
          clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }	
      return true;
    default:
      return true;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case EPRM:
            eeconfig_init();
            return false;
        case SHRINK_WINDOW:
            SEND_STRING(SS_LCTRL("x") "{");
            return false;
        case ENLARGE_WINDOW:
            SEND_STRING(SS_LCTRL("x") "}");
            return false;        
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);  
  switch (layer) {
      case 0:        
        break;
      case 1:
        ergodox_right_led_1_on();        
        break;
      case 2:
        ergodox_right_led_2_on();        
        break;
      case 3:
        ergodox_right_led_3_on();        
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();        
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();        
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();        
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();        
        break;
      default:
        break;
  }
  return state;
};
