#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16
#define undo LCTL(KC_Z)
#define redo LCTL(KC_Y)
#define copy LCTL(KC_C)
#define paste LCTL(KC_V)
#define shleft LSFT(KC_LEFT)
#define shdown LSFT(KC_DOWN)
#define shup LSFT(KC_UP)
#define shright LSFT(KC_RGHT)
#define shhome LSFT(KC_HOME)
#define shend LSFT(KC_END)


enum custom_keycodes {
  QWERTY=SAFE_RANGE,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
};

// macros
enum marco_keycodes{
  PRN=500,
  CBR,
  BRC,
};

//Tap dance definitions
enum tap_dance_keycodes{
  TAP_LPRN_RPRN=0, // ( / )
  TAP_LCBR_RCBR, // { / }
  TAP_LBRC_RBRC, // [ / ]
  TAP_SLSH_MINS, // / / _
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TAP_LPRN_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [TAP_LCBR_RCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [TAP_LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TAP_SLSH_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_MINS),
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |  Alt |Adjust|Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_LCTRL,KC_LGUI, KC_LALT, ADJUST,  LOWER,   KC_SPC,  KC_SPC,  TT(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  / _ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Adjust| Alt  | GUI  |Lower |Space |Shift |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = KEYMAP( \
  KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_DEL,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    TD(TAP_SLSH_MINS), \
  KC_TAB,  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  KC_LCTL, ADJUST , KC_LALT, KC_LGUI, LOWER,   KC_SPC,  OSM(KC_LALT),  TT(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, shhome, shleft, shdown, shup, shright, shend, \
  KC_DEL,  copy,    undo,    redo,    paste,   KC_F5,   KC_HOME,KC_LEFT,KC_DOWN,KC_UP,KC_RGHT, KC_END, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),
// /* Lower
//  * ,-----------------------------------------------------------------------------------.
//  * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |shleft|shdown| shup |shrigh| Del  |
//  * |------+------+------+------+------+-------------+------+------+------+------+------|
//  * | Del  | undo | redo | copy |paste |  F5  | home | left | down |  up  | right|  end |
//  * |------+------+------+------+------+------|------+------+------+------+------+------|
//  * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
//  * |------+------+------+------+------+------+------+------+------+------+------+------|
//  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
//  * `-----------------------------------------------------------------------------------'

/* Raise
 *  ,-----------------------------------------------------------------------------------.
 * |      |   !  |      |      |   $  |   %  |   ^  |   &  |   *  |   +  |   -  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  1   |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |   @  |   #  | ( / )| { / }| [ / ]|   =  |  ()  |  {}  |  []  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | win  | undo | redo | copy |paste |Space |Space |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  _______, KC_EXLM, _______, _______, KC_DLR, KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_MINS, _______, \
  _______,  KC_1,    KC_2,   KC_3,    KC_4,   KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, _______,  KC_AT,  KC_HASH,  TD(TAP_LPRN_RPRN) ,  TD(TAP_LCBR_RCBR) ,  TD(TAP_LBRC_RBRC) ,  KC_EQL, PRN , CBR , BRC , _______, \
  _______, undo, redo, copy, paste, _______, _______, _______, _______, _______, _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |RESET |      |      |      |      |QWERTY|DVORAK|      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  RESET  , _______, _______, _______, _______, QWERTY, DVORAK,   _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_RAISE);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    //   break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
     //macro stuff
  switch (keycode) {
    case PRN:
      if (record->event.pressed){
        SEND_STRING("()"SS_TAP(X_LEFT));
      }
      return false;
      break;
    case CBR:
      if (record->event.pressed){
        SEND_STRING("{}"SS_TAP(X_LEFT));
      }
      return false;
      break;
    case BRC:
      if (record->event.pressed){
        SEND_STRING("[]"SS_TAP(X_LEFT));
      }
      return false;
      break;
  }
  return true;
}