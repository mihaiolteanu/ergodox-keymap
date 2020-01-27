#include QMK_KEYBOARD_H
#include "version.h"

#define _____ KC_TRNS
#define __x__ KC_NO

/* A blank layout. Used to simulate key holds. */
#define LAYOUT(name) [name] = LAYOUT_ergodox(\
  _____, _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____,\
                                     _____, _____,\
                                            _____,\
                              _____, _____, _____,\
  _____, _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____, _____, _____,\
         _____, _____, _____, _____, _____, _____,\
  _____, _____, _____, _____, _____, _____, _____,\
                _____, _____, _____, _____, _____,\
  _____, _____,\
  _____,\
  _____, _____, _____)

enum layer_codes {
      BASE = 0,                 /* Default layer */
      XWINDOW,
      EMACS,
      SYMBOLS,
      SYMBOLS_2,
      MDIA,
      EHELP,                    /* Emacs Help */
      EVC,                      /* Emacs Version Control */
      EX,                       /* Emacs C-x */
      BLANK
};

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  SHRINK_WINDOW,                /* Emacs, shrink-window-horizontally */
  ENLARGE_WINDOW,               /* Emacs, enlarge-window-horizontally */
  VRSN,
  RGB_SLD,
  EMACS_TO_BASE,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

enum tap_dances {
    TD_SYMBOLS,
    TD_EMACS
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

int  cur_dance    (qk_tap_dance_state_t *state);

void symbols_finished (qk_tap_dance_state_t *state, void *user_data);
void symbols_reset    (qk_tap_dance_state_t *state, void *user_data);
void movement_finished (qk_tap_dance_state_t *state, void *user_data);
void movement_reset    (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SYMBOLS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, symbols_finished, symbols_reset),
  [TD_EMACS]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, movement_finished, movement_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer */
[BASE] = LAYOUT_ergodox(
  LCTL(KC_F1),   KC_VOLD, KC_VOLU, __x__,       __x__,         KC_F6, RESET,
  __x__,         __x__,   KC_W,    KC_E,        KC_R,          KC_T,  __x__,
  __x__, KC_A,   KC_S,    WIN_T(KC_D), ALT_T(KC_F),   KC_G,
  OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,        LT(EVC, KC_V), KC_B,  __x__,
  TG(EMACS),     __x__,   __x__,   __x__,      __x__,
                                                               __x__,  __x__,
                                                                       __x__,
                                 LT(XWINDOW, KC_BSPC), CTL_T(KC_SPC), KC_TAB,

  __x__, __x__,  __x__,       __x__,       __x__,       __x__,  __x__,
  __x__, KC_Y,   KC_U,        KC_I,        KC_O,        __x__,  __x__,
  LT(EHELP, KC_H), ALT_T(KC_J), WIN_T(KC_K), KC_L, KC_P, TG(MDIA),
  __x__, KC_N,   KC_M,        KC_COMMA,    KC_DOT,      KC_Q,   OSM(MOD_RSFT),
                 __x__,      __x__,       __x__,       __x__,  __x__,
  __x__, __x__,
  __x__,
  LT(MDIA, KC_ESC), CTL_T(KC_ENT), TD(TD_SYMBOLS)),


[XWINDOW] = LAYOUT_ergodox(
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, KC_F5,  KC_F3, KC_F4, _____, 
  _____, _____, _____,  _____, _____, _____, _____,
  _____, _____, _____,  _____, _____,
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
  _____, KC_F1, KC_F2
),


[EMACS] = LAYOUT_ergodox(
  _____, _____,   _____,     _____,   _____,     _____,   _____,
  _____, _____,   LCA(KC_B), C(KC_P), LCA(KC_F), A(KC_V), _____,
  _____, C(KC_A), C(KC_B),   C(KC_N), C(KC_F),   C(KC_E),
  _____, _____,   _____,     _____,    _____,    C(KC_V), _____,
  _____, _____,   _____,     _____,    _____,
                                                   _____, _____,
                                                          _____,
                            EMACS_TO_BASE, LCA(KC_SPACE), _____,
  
  _____, _____,  ENLARGE_WINDOW,   _____, SHRINK_WINDOW,  _____,          _____,
  _____, _____,  C(KC_Y), C(KC_W),        _____,        _____,          _____,
         KC_DEL, C(KC_D), A(KC_D),        G(KC_K),      C(KC_K),        _____,  
  _____, _____,  _____,   LCTL(KC_COMMA), LCTL(KC_DOT), LCTL(KC_SLASH), _____,
                 _____,    _____,         _____,        _____,          _____,
  _____, _____,
  _____,
  _____, LCA(KC_SPACE), TO(BASE)
),

   
[SYMBOLS] = LAYOUT_ergodox(
  _____, _____, _____, _____, _____, _____, _____,
  _____, _____, KC_1,  KC_2,  KC_3,  _____, _____,
  _____, _____, KC_4,  KC_5,  KC_6,  _____,
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
  _____, _____, _____
),


[SYMBOLS_2] = LAYOUT_ergodox(
  _____, _____,               _____,       _____,         _____,         _____,        _____,
  _____, _____,               KC_PIPE,     KC_PLUS,       KC_ASTERISK,   KC_AT,        _____,
  _____, KC_LEFT_CURLY_BRACE, KC_LBRACKET, KC_MINUS,      KC_LEFT_PAREN, KC_AMPERSAND,
  _____, _____,               _____,       KC_UNDERSCORE, KC_EQUAL,      KC_TILDE,     _____,
  _____, _____,               _____,       _____,         _____,
                                                                                _____, _____,
                                                                                       _____,
                                                              KC_QUESTION, KC_EXCLAIM, _____,
                                      
  _____, _____,         _____,           _____,                 _____,                  _____,     _____,
  _____, KC_CIRCUMFLEX, KC_COLON,        KC_SCOLON,             _____,                  _____,     _____,
         KC_HASH,       KC_DOUBLE_QUOTE, KC_QUOTE,              KC_GRAVE,               _____,     _____,
  _____, KC_PERCENT,    KC_SLASH,        KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET, KC_BSLASH, _____,
                        _____,           _____,                  _____,                 _____,     _____,
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
  
  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, _____,
  _____,   RGB_HUI, RGB_SAI, RGB_VAI,  RGB_M_K,  RGB_M_X, _____,
           RGB_HUD, RGB_SAD, RGB_VAD,  RGB_M_G,  RGB_M_T, _____,
  _____,   _____,   RGB_MOD, RGB_RMOD, _____,    _____,   _____,
                    KC_VOLU, KC_VOLD,  KC_MUTE,  _____,   _____,
  _____, _____,
  _____,
  _____, _____, _____),

LAYOUT(EHELP),
LAYOUT(EVC),

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
  _____, _____, _____
),

};


int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed)
        return SINGLE_HOLD;
    else
        return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed)
        return DOUBLE_HOLD;
    else
        return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)
        return TRIPLE_TAP;
    else
        return TRIPLE_HOLD;
  }
  else return 8;
}

static tap symbols_tap_state = {
  .is_press_action = true,
  .state = 0
};

void symbols_finished (qk_tap_dance_state_t *state, void *user_data) {
  symbols_tap_state.state = cur_dance(state);
  switch (symbols_tap_state.state) {
    case SINGLE_TAP:
        set_oneshot_layer(SYMBOLS_2, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        break;
    case SINGLE_HOLD:
        /* register_code(KC_RCTRL); */
        layer_on(SYMBOLS);
        break;
    case DOUBLE_TAP:
        set_oneshot_layer(SYMBOLS_2, ONESHOT_START);
        set_oneshot_layer(SYMBOLS_2, ONESHOT_PRESSED);
        break;
    case DOUBLE_HOLD:
        register_code(KC_LALT);        
        break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void symbols_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (symbols_tap_state.state) {
    case SINGLE_TAP:
        break;
    case SINGLE_HOLD:
        layer_off(SYMBOLS);
        /* unregister_code(KC_RCTRL); */
        break;
    case DOUBLE_TAP:
        break;
    case DOUBLE_HOLD:
        
        unregister_code(KC_RCTRL);
        break;
  }
  symbols_tap_state.state = 0;
}

static tap movement_tap_state = {
  .is_press_action = true,
  .state = 0
};

void movement_finished (qk_tap_dance_state_t *state, void *user_data) {
    movement_tap_state.state = cur_dance(state);
    switch (movement_tap_state.state) {
    case SINGLE_TAP:
        layer_on(EMACS);
        tap_code16(MEH(KC_M));
        break;
    case SINGLE_HOLD:
        layer_on(EMACS);
        tap_code16(MEH(KC_M));
        break;
    case DOUBLE_TAP:
        register_code(KC_ESC);
        break;
    case DOUBLE_HOLD:
        break;
  }
}

void movement_reset  (qk_tap_dance_state_t *state, void *user_data) {
    switch (movement_tap_state.state) {
    case SINGLE_TAP:
        break;
    case SINGLE_HOLD:
        layer_off(EMACS);
        tap_code16(MEH(KC_I));
        break;
    case DOUBLE_TAP:
        break;
    case DOUBLE_HOLD:
        break;
  }
}

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
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
#ifdef RGBLIGHT_ENABLE
        case RGB_SLD:
            rgblight_mode(1);
            return false;
#endif
        case EMACS_TO_BASE:
            layer_off(EMACS);
            layer_on(BASE);
            tap_code16(MEH(KC_I));
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
      case EHELP:
          SEND_STRING(SS_LCTRL("h"));
          break;
      case EVC:
          SEND_STRING(SS_LCTRL("x") "v");
          break;
  
  }
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif        
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
