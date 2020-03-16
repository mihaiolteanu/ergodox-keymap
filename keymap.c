#include QMK_KEYBOARD_H
#include "version.h"

#define _____ KC_TRNS
#define __x__ KC_NO

enum layer_codes {
      BASE = 0,                 /* Default layer */
      XWINDOW,
      EMACS_L,
      EMACS_R,
      NUMERIC,
      NUM_UP,                   /* Shifted numeric symbols */
      SYMBOLS,      
      MDIA,      
      BLANK
};

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  EM_WIN_S,                /* Emacs, shrink-window-horizontally */
  EM_WIN_L,                /* Emacs, enlarge-window-horizontally */
  EM_SPLIT,                /* Emacs, split-window-right */
  EM_UNSPLIT,              /* Emacs, delete-window */
  EM_KILL,                 /* Emacs, kill-buffer */
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
  LCTL(KC_F1),   KC_VOLD, KC_VOLU,        __x__,       __x__,       KC_F6, RESET,
  __x__,         __x__,   KC_W,           KC_E,        KC_R,        KC_T,  __x__,
  __x__,         KC_A,    WIN_T(KC_S),    ALT_T(KC_D), CTL_T(KC_F), KC_G,
  OSM(MOD_LSFT), KC_Z,    KC_X,           KC_C,        KC_V,        KC_B,  __x__,
  TG(EMACS_L),   __x__,   __x__,          __x__,       __x__,
                                                                     __x__,  __x__,
                                                                             __x__,
                                 LT(EMACS_R, KC_BSPC), LT(XWINDOW, KC_SPC), KC_TAB,

  __x__, __x__, __x__,             __x__,             __x__,       __x__,  __x__,
  __x__, KC_Y,  LT(NUM_UP, KC_U),  LT(NUMERIC, KC_I), KC_O,        __x__,  __x__,
         KC_H,  CTL_T(KC_J),       LT(SYMBOLS, KC_K), ALT_T(KC_L), KC_P,   TG(MDIA),
  __x__, KC_N,  KC_M,              KC_COMMA,          KC_DOT,      KC_Q,   OSM(MOD_RSFT),
                __x__,             __x__,             __x__,       __x__,  __x__,
  __x__, __x__,
  __x__,
  LT(MDIA, KC_ESC), LT(EMACS_L, KC_ENT), __x__),



[XWINDOW] = LAYOUT_ergodox(
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____, _____, 
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____,
                                      _____, _____,
                                             _____,
                               _____, _____, _____,
                                      
  _____, _____, _____, _____,   _____,   _____, _____,
  _____, _____, _____, G(KC_B), _____,   _____, _____,
         _____, KC_F4, KC_F3,   G(KC_T), KC_F5, _____,
  _____, _____, _____, _____,   _____,   _____, _____,
                _____, _____,   _____,   _____, _____,
  _____, _____,
  _____,
  _____, KC_F1, KC_F2
),



[EMACS_L] = LAYOUT_ergodox(
  _____, _____,       EM_WIN_L, EM_SPLIT, EM_WIN_S, _____,   _____,
  _____, _____,       _____,    C(KC_P),  _____,    _____,   _____,
  _____, C(KC_A),     C(KC_B),  C(KC_N),  C(KC_F),  C(KC_E),
  _____, C(KC_SLASH), C(KC_X),  _____,    _____,    _____,   _____,
  _____, _____,       _____,    _____,    _____,
                                                      _____, _____,
                                                             _____,
                  /*C(S(KC_SPC))*/KC_DEL, C(KC_TAB), LCA(KC_SPACE),
  
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, _____, _____, _____, _____, _____,
         _____, _____, _____, _____, _____, _____,  
  _____, _____, _____, _____, _____, _____, _____,
                _____, _____, _____, _____, _____,
  _____, _____,
  _____,
  _____, _____, _____),



[EMACS_R] = LAYOUT_ergodox(
  _____, _____, _____,   _____,   _____,   _____, _____,
  _____, _____, _____,   _____,   _____,   _____, _____,
  _____, _____, _____,   _____,   _____,   _____,
  _____, _____, _____,   _____,   _____,   _____, _____,
  _____, _____, _____,   _____,   _____,
                                           _____, _____,
                                                  _____,
                                    _____, _____, _____,
                                      
  _____, _____, _____, EM_UNSPLIT, _____, _____, _____,
  _____, _____, _____, _____,      _____, _____, _____,
         _____, _____, _____,      _____, _____, _____,
  _____, _____, _____, _____,      _____, _____, _____,
                _____, _____,      _____, _____, _____,
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
  _____, KC_QUESTION, KC_AMPERSAND, KC_ASTERISK, _____,         _____, _____,
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
  _____, _____,     KC_LBRC,   KC_RBRC,  KC_LCBR,  KC_RCBR,  _____,
  _____, KC_TILDE,  _____,     KC_QUOTE, KC_DQUO,  KC_GRAVE, _____,
  _____, KC_SCOLON, KC_COLON,  KC_MINUS, KC_LPRN,  KC_RPRN, 
  _____, KC_SLASH,  KC_BSLASH, KC_EQUAL, KC_PLUS,  KC_UNDS,  _____,
  _____, _____,     KC_PIPE,   KC_LABK,  KC_RABK,
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
        case EM_WIN_S:
            SEND_STRING(SS_LCTRL("x") "{");
            return false;
        case EM_WIN_L:
            SEND_STRING(SS_LCTRL("x") "}");
            return false;        
        case EM_SPLIT:
            SEND_STRING(SS_LCTRL("x") "3");
            return false;        
        case EM_UNSPLIT:
            SEND_STRING(SS_LCTRL("x") "0");
            return false;        
        case EM_KILL:
            SEND_STRING(SS_LCTRL("x") "k");
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
      case EMACS_L:
        ergodox_right_led_1_on();        
        break;
      case MDIA:
        ergodox_right_led_2_on();        
        break;
      case XWINDOW:
        ergodox_right_led_3_on();        
        break;      
      default:
        break;
  }
  return state;
};
