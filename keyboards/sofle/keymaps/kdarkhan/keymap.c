#include "keycodes.h"

#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif

#include QMK_KEYBOARD_H

// enum encoder_state { vol_page, vol_hor,  hor_ver, vol_bri};
// static encoder_state cur_enc_state = vol_page;
enum my_keycodes {
    MC_ENC1 = SAFE_RANGE,
    MC_ENC2,
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {[0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)}, [1] = {ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(_______, _______)}, [2] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [3] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [4] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}};
#else
enum enc1_layer { ENC1_VOL = 0, ENC1_BRI, ENC1_MOUSE, ENC1_MOUSE_SCROLL, ENC1_END };

enum enc2_layer {
    ENC2_LEFT_RIGHT = 0,
    ENC2_PAGE,
    ENC2_MOUSE,
    ENC2_MOUSE_SCROLL,
    ENC2_END,
};
static uint8_t current_enc1_layer = 0;
static uint8_t current_enc2_layer = 0;

const static uint16_t enc1_map[ENC1_END][3] = {
    [0] = {KC_VOLD, KC_VOLU, KC_MUTE},
    [1] = {KC_BRID, KC_BRIU, KC_MUTE},
    [2] = {MS_LEFT, MS_RGHT, MS_BTN1},
    [3] = {MS_WHLD, MS_WHLU, MS_BTN1},
};

const static uint16_t enc2_map[ENC2_END][3] = {
    [0] = {KC_LEFT, KC_RIGHT, KC_UP},
    [1] = {KC_PGDN, KC_PGUP, KC_HOME},
    [2] = {MS_DOWN, MS_UP, MS_BTN2},
    [3] = {MS_WHLL, MS_WHLR, MS_BTN2},
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        tap_code(enc1_map[current_enc1_layer][clockwise]);
    } else { /* Second encoder */
        tap_code(enc2_map[current_enc2_layer][clockwise]);
    }
    return false;
}
#endif

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _GAME,
    _ARROWS,
    _ADJ1,
    _ADJ2,
    _ADJ3,
    _ADJ4,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,            KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                          KC_6,      KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
  LT(_ADJ4, KC_TAB), KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                          KC_Y,      KC_U,         KC_I,         KC_O,         KC_P,            LT(_ADJ3, KC_BSLS),
  LT(_ADJ1, KC_ESC), KC_A,         KC_S,         KC_D,         KC_F,         KC_G,                          KC_H,      KC_J,         KC_K,         KC_L,         KC_SCLN,         KC_QUOT,
  KC_LSFT,           KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,      MC_ENC1,   MC_ENC2, KC_N,      KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RSFT,
                     MO(_ADJ2),    KC_LALT,      KC_LCTL,      KC_SPC,       KC_LGUI,                       KC_BSPC,   KC_ENT,       KC_RCTL,      KC_RALT,      KC_RGUI
),

[_GAME] = LAYOUT(
  KC_GRV,            KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                          KC_6,      KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
  KC_TAB,            KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                          KC_Y,      KC_U,         KC_I,         KC_O,         KC_P,            LT(_ADJ3, KC_BSLS),
  KC_ESC,            KC_A,         KC_S,         KC_D,         KC_F        , KC_G,                          KC_H,      KC_J,         KC_K,         KC_L,         KC_SCLN,         KC_QUOT,
  KC_LSFT,           KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,      MC_ENC1,   MC_ENC2, KC_N,      KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_RSFT,
                     MO(_ADJ2),    KC_LALT,      KC_LCTL,      KC_SPC,       KC_LGUI,                       KC_BSPC,   KC_ENT,       KC_RCTL,      KC_RALT,      KC_RGUI
),

[_ARROWS] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,                      _______,    _______,   _______,   _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,                      _______,    _______,   _______,   _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,                      _______,    _______,   _______,   _______,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______, _______,    _______, _______,    _______,   KC_UP,     _______,  _______,  _______,
            _______,  _______,  _______,  _______,  _______,                      _______,    _______,   KC_LEFT,   KC_DOWN,  KC_RIGHT
),

[_ADJ1] = LAYOUT(
  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,        KC_F5,                            KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
  KC_UNDO,  KC_WREF,  _______,  KC_QUOT,  KC_DQUO,      _______,                          KC_CIRC,    KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  KC_F12,
  _______,  KC_WHOM,  _______,  KC_UNDS,  KC_PLUS,      _______,                          KC_LEFT,    KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,
  KC_WBAK,  KC_WFWD,  _______,  _______,  _______,      _______,     _______,    _______, KC_ASTR,    KC_LPRN,  KC_RPRN,  KC_AMPR,  KC_EQL,  _______,
            _______,  _______,  _______,  LSFT(KC_SPC), TT(_ARROWS),                      KC_DEL,     _______,  _______,  KC_HOME,  KC_END
),

[_ADJ2] = LAYOUT(
  _______,  _______,  _______,  _______,      _______, _______,                      _______,    _______,  _______,  _______, _______,  _______,
  KC_TAB,   KC_INS,   KC_APP,   _______,      _______, _______,                      _______,    _______,  _______,  _______, _______,  _______,
  _______,  KC_PSCR,  _______,  DF(_QWERTY),  _______, _______,                      _______,    _______,  _______,  _______, _______,  _______,
  _______,  _______,  _______,  DF(_GAME), _______, _______, _______,    _______, _______,    _______,  _______,  _______, _______,  _______,
            _______,  _______,  _______,      _______, _______,                      _______,    _______,  _______,  _______, _______
),

[_ADJ3] = LAYOUT(
  _______,  KC_F1,    KC_F2,       KC_F3,      KC_F4,      KC_F5,                        KC_F6,      KC_F7,    KC_F8,     KC_F9,   KC_F10,   KC_F11,
  _______,  _______,  MS_BTN1,  MS_UP,    MS_BTN2, _______,                      _______,    _______,  _______,   _______, _______,  _______,
  KC_CAPS,  _______,  MS_LEFT,     MS_DOWN,    MS_RGHT,    _______,                      _______,    _______,  _______,   _______, _______,  _______,
  _______,  _______,  MS_WHLD,     _______,    MS_WHLU,    _______, _______,    _______, _______,    _______,  _______,   _______, _______,  _______,
                      KC_MPRV,     KC_MPLY,    KC_MNXT,    _______, _______,    _______, _______,    _______,  _______,   _______
),

[_ADJ4] = LAYOUT(
  _______, _______,  _______,                _______,                _______,                _______,                      KC_VOLD,    KC_VOLU,   KC_BRID,   KC_BRIU,  KC_MPRV,  KC_MNXT,
  _______, _______,  _______,                OSM(MOD_LALT|MOD_LCTL), OSM(MOD_LSFT|MOD_LCTL), _______,                      KC_NUM,     KC_KP_7,   KC_KP_8,   KC_KP_9,  KC_PMNS,  KC_MPLY,
  KC_LGUI, _______,  OSM(MOD_LGUI|MOD_LALT), OSM(MOD_LGUI|MOD_LSFT), OSM(MOD_LGUI),          _______,                      _______,    KC_KP_3,   KC_KP_5,   KC_KP_6,  KC_PAST,  _______,
  _______, _______,  _______,                _______,                _______,                _______, _______,    _______, KC_KP_0,    KC_KP_1,   KC_KP_2,   KC_KP_3,  KC_PSLS,  _______,
           _______,  _______,                _______,                _______,                _______,                      _______,    _______,   _______,   _______,  _______
),
};
// clang-format on

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // SMTD_MT(KC_A, KC_LEFT_GUI)
        // SMTD_MT(KC_S, KC_LEFT_ALT)
        // SMTD_MT(KC_D, KC_LEFT_CTRL)
        // SMTD_MT(KC_F, KC_LSFT)
        SMTD_MT(KC_A, KC_LSFT)
        SMTD_MT(KC_S, KC_LALT)
        SMTD_MT(KC_D, KC_LCTL)
        SMTD_MT(KC_F, KC_LGUI)

        SMTD_MT(KC_J, KC_RGUI)
        SMTD_MT(KC_K, KC_RCTL)
        SMTD_MT(KC_L, KC_RALT)
        SMTD_MT(KC_SCLN, KC_RSFT)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

static uint8_t enc1_kc, enc2_kc;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MC_ENC1:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    current_enc1_layer = (current_enc1_layer + 1) % ENC1_END;
                } else {
                    enc1_kc = enc1_map[current_enc1_layer][2];
                    register_code(enc1_kc);
                }
            } else {
                unregister_code(enc1_kc);
            }
            return false;

        case MC_ENC2:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    current_enc2_layer = (current_enc2_layer + 1) % ENC2_END;
                } else {
                    enc2_kc = enc2_map[current_enc2_layer][2];
                    register_code(enc2_kc);
                }
            } else {
                unregister_code(enc2_kc);
            }
            return false;
    }

    return true;
}

#ifdef OLED_ENABLE
#    include "matrix.h"
#    include OLED_FONT_H

extern matrix_row_t matrix[MATRIX_ROWS];

#    define ANIM_FRAME_DURATION 100
#    define IDLE_FRAMES 5
#    define IDLE_TIMEOUT 750
#    define SLEEP_TIMEOUT 15000

static bool OLED_redraw = true;

static const uint8_t bongofont[] PROGMEM = {0xC1, 0xC1, 0xC2, 0x04, 0x08, 0x10, 0xC0, 0x38, 0x04, 0x03, 0x00, 0x00, 0xA0, 0x22, 0x24, 0x14, 0x12, 0x12, 0xA0, 0x21, 0x22, 0x12, 0x11, 0x11, 0x83, 0x7C, 0x41, 0x41, 0x40, 0x40, 0x82, 0x82, 0x84, 0x08, 0x10, 0x20, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0x19, 0x06, 0x00, 0x00, 0x80, 0x70, 0x0C, 0x03, 0x00, 0x00, 0x80, 0x00, 0x30, 0x30, 0x00, 0xC0, 0x80, 0x00, 0x30, 0x30, 0x00, 0x00, 0x49, 0x88, 0x08, 0x08, 0x08, 0x00, 0x44, 0x84, 0x04, 0x04, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x3C, 0xC2, 0x01, 0x01, 0x02, 0x02, 0x35, 0x01, 0x8A, 0x7C, 0x00, 0x00, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x20, 0x21, 0x22, 0x12, 0x11, 0x11, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x1E, 0xE1,
                                            0x00, 0x00, 0x01, 0x01, 0x1C, 0xE2, 0x01, 0x01, 0x02, 0x02, 0x18, 0x64, 0x82, 0x02, 0x02, 0x02, 0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 0x18, 0x18, 0x1B, 0x03, 0x00, 0x40, 0x18, 0x06, 0x05, 0x98, 0x99, 0x84, 0x12, 0x0B, 0x08, 0x08, 0x08, 0x08, 0x11, 0x09, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0xD0, 0x11, 0x0F, 0x21, 0x10, 0x10, 0x10, 0x11, 0x0F, 0x01, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x10, 0x08, 0x04, 0x02, 0x02, 0x04, 0x0C, 0x30, 0x40, 0x80, 0x00, 0x00, 0x0C, 0x0C, 0x0D, 0x01, 0x00, 0x40, 0x08, 0xE8, 0x08, 0x07, 0x10, 0x24, 0x08, 0x30, 0x40, 0x80, 0x00, 0x00, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x08, 0x08, 0x04, 0x02, 0x02, 0x02, 0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x05, 0x05, 0x09, 0x09, 0x10, 0x10, 0x04, 0x38, 0x40, 0x80,
                                            0x00, 0x00, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x02, 0x02, 0x81, 0x80, 0x80, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01, 0xE1, 0x1A, 0x06, 0x09, 0x31, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x00, 0x00, 0x60, 0x60, 0x00, 0x81, 0x00, 0x00, 0x01, 0x01, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const uint8_t bongo_line_x[]   = {51, 49, 48, 57};
static const uint8_t bongo_line_y[]   = {0, 8, 16, 24};
static const uint8_t bongo_line_len[] = {5, 7, 8, 6};

const uint8_t bongo_line_data[8][26] PROGMEM = {{// idle1
                                                 60, 52, 19, 30, 35, 22, 47, 51, 60, 9, 0, 17, 1, 57, 33, 3, 27, 41, 29, 50, 45, 36, 60, 60, 60, 60},
                                                {// idle2
                                                 60, 52, 19, 30, 35, 22, 47, 51, 60, 9, 0, 17, 1, 57, 33, 3, 27, 41, 29, 50, 45, 36, 60, 60, 60, 60},
                                                {// idle3
                                                 60, 53, 14, 31, 23, 15, 43, 60, 60, 54, 5, 13, 7, 56, 24, 2, 26, 39, 29, 50, 45, 36, 60, 60, 60, 60},
                                                {// idle4
                                                 6, 52, 19, 38, 32, 20, 47, 51, 60, 9, 0, 17, 8, 57, 33, 3, 27, 41, 29, 50, 45, 36, 60, 60, 60, 60},
                                                {// idle5
                                                 60, 52, 19, 37, 40, 21, 47, 51, 60, 9, 0, 17, 8, 57, 33, 3, 27, 41, 29, 50, 45, 36, 60, 60, 60, 60},
                                                {// prep
                                                 6, 52, 19, 38, 32, 20, 44, 51, 60, 10, 48, 16, 8, 25, 4, 18, 27, 42, 46, 50, 60, 60, 60, 60, 60, 60},
                                                {// tap1
                                                 6, 52, 19, 38, 32, 20, 44, 51, 60, 10, 49, 17, 8, 25, 4, 18, 27, 41, 28, 11, 60, 60, 60, 60, 58, 59},
                                                {// tap2
                                                 6, 52, 19, 38, 32, 20, 47, 51, 60, 10, 48, 16, 8, 60, 55, 3, 27, 42, 46, 50, 45, 34, 12, 60, 60, 60}};

enum anin_states { sleep, idle, prep, tap };
uint8_t  anim_state         = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer         = 0;
uint8_t  current_idle_frame = 0;
uint8_t  current_tap_frame  = 6;
uint8_t  last_bongo_frame   = 12;

void write_bongochar_at_pixel_xy(uint8_t x, uint8_t y, uint8_t data, bool invert) {
    uint8_t i, j, temp;
    for (i = 0; i < 6; i++) { // 6 = font width
        temp = pgm_read_byte(&bongofont[data * 6] + i);
        for (j = 0; j < 8; j++) { // 8 = font height
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
    }
}

bool is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > 0) {
            return true;
        }
    }
    return false;
}

void eval_anim_state(void) {
    bool key_down;
    key_down = is_key_down();

    switch (anim_state) {
        case sleep:
            if (key_down) {
                anim_state = tap;
            }
            break;
        case idle:
            if (key_down) {
                anim_state = tap;
            } else if (timer_elapsed32(idle_timeout_timer) >= SLEEP_TIMEOUT) // prep to idle
            {
                anim_state         = sleep;
                current_idle_frame = 0;
            }
            break;
        case prep:
            if (key_down) {
                anim_state = tap;
            } else if (timer_elapsed32(idle_timeout_timer) >= IDLE_TIMEOUT) // prep to idle
            {
                anim_state         = idle;
                current_idle_frame = 0;
            }
            break;
        case tap:
            if (!key_down) {
                anim_state         = prep;
                idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void draw_bongo_table(void) {
    // draws the table edge for bongocat, this edge doesn't change during the
    // animation
    uint8_t i;
    uint8_t y = 31;
    uint8_t j = 0;
    for (i = 17; i < 57; i++) {
        oled_write_pixel(i, y, true); // every five horizontal pixels, move up one
                                      // pixel to make a diagonal line
        if (j == 4) {
            --y;
            j = 0;
        } else {
            j++;
        }
    }

    y = 15;
    j = 0;
    for (i = 91; i < 128; i++) {
        oled_write_pixel(i, y, true); // every four horizontal pixels, move up one
                                      // pixel to make a diagonal line
        if (j == 3) {
            --y;
            j = 0;
        } else {
            j++;
        }
    }
}

void draw_bongocat_frame(int framenumber) {
    // only redraw if the animation frame has changed
    if (framenumber != last_bongo_frame) {
        last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                write_bongochar_at_pixel_xy(bongo_line_x[i] + j * 6, bongo_line_y[i], pgm_read_byte(&bongo_line_data[framenumber][current_bongochar]), false);
                current_bongochar++;
            }
        }
    }
}

bool is_new_tap(void) {
    static matrix_row_t old_matrix[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool                new_tap      = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > old_matrix[i]) { // more 1's detected, there was a new tap
            new_tap = true;
        }
        old_matrix[i] = matrix[i];
    }
    return new_tap;
}

void draw_bongocat(void) {
    static bool already_tapped = false;
    if (is_new_tap()) {
        already_tapped = false;
    };
    eval_anim_state();
    switch (anim_state) {
        case sleep:
            draw_bongocat_frame(4);
            break;
        case idle:
            draw_bongocat_frame(4 - current_idle_frame);
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                current_idle_frame = (current_idle_frame + 1) % 5;
                anim_timer         = timer_read32();
            }
            break;
        case prep:
            draw_bongocat_frame(5);
            already_tapped = false;
            break;
        case tap:
            draw_bongocat_frame(current_tap_frame);
            if (already_tapped == false) {
                if (current_tap_frame == 6) {
                    current_tap_frame = 7;
                } else {
                    current_tap_frame = 6;
                }
            }
            already_tapped = true;
            break;
        default:
            draw_bongocat_frame(4);
            already_tapped = false;
            break;
    }
}

bool oled_right_task_user(void) {
    if (OLED_redraw) {
        oled_clear();
        last_bongo_frame = 12; // force a redraw
        draw_bongo_table();
        OLED_redraw = false;
    }
    draw_bongocat();
    return false;
}

static os_variant_t prev_detected_os = OS_UNSURE;

bool process_detected_host_os_kb(os_variant_t detected_os) {
    prev_detected_os = detected_os;
    return true;
}

static uint8_t default_layer = _QWERTY;
layer_state_t  default_layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
        case _QWERTY:
            default_layer = _QWERTY;
            break;
        case _GAME:
            default_layer = _GAME;
            break;
    };
    return state;
}

bool oled_led_task_user(void) {
    oled_write_ln("LAY:", false);
    oled_write_ln(default_layer == _QWERTY ? " qwe\n" : " gam\n", false);

    switch (current_enc1_layer) {
        case ENC1_VOL:
            oled_write_ln("1-vo", false);
            break;
        case ENC1_BRI:
            oled_write_ln("1-br", false);
            break;
        case ENC1_MOUSE:
            oled_write_ln("1-ms", false);
            break;
        case ENC1_MOUSE_SCROLL:
            oled_write_ln("1-wh", false);
            break;
        default:
            oled_write_ln("1-??", false);
    }

    switch (current_enc2_layer) {
        case ENC2_LEFT_RIGHT:
            oled_write_ln("2-lr", false);
            break;
        case ENC2_PAGE:
            oled_write_ln("2-pg", false);
            break;
        case ENC2_MOUSE:
            oled_write_ln("2-ms", false);
            break;
        case ENC2_MOUSE_SCROLL:
            oled_write_ln("2-wh", false);
            break;
        default:
            oled_write_ln("1-??", false);
    }

    // Print current layer
    /*
    switch (get_highest_layer(layer_state)) {
      case 0:
        oled_write_ln(" bas", false);
        break;
      case 1:
        oled_write_ln(" one", false);
        break;
      case 2:
        oled_write_ln(" two", false);
        break;
      case 3:
        oled_write_ln(" thr", false);
        break;
      case 4:
        oled_write_ln(" for", false);
        break;
      default:
        oled_write_ln(" und", false);
    }*/

    oled_write_ln("\nOS:", false);
    switch (prev_detected_os) {
        case OS_LINUX:
            oled_write_ln(" lin", false);
            break;
        case OS_WINDOWS:
            oled_write_ln(" win", false);
            break;
        case OS_MACOS:
            oled_write_ln(" mac", false);
            break;
        case OS_IOS:
            oled_write_ln(" ios", false);
            break;
        default:
            oled_write_ln(" ???", false);
            break;
    }

    led_t led_usb_state = host_keyboard_led_state();
    // If caps lock is on, then blink CAPS text
    if (led_usb_state.caps_lock) {
        oled_write_ln((timer_read32() % 1000 > 500) ? "\nCAP:\n yes" : "\n    \n  ", false);
    } else {
        oled_write_ln("\nCAP:\n no", false);
    }

    // oled_write_ln(led_usb_state.caps_lock ? " yes" : " no", false);
    oled_write_ln("\nNUM:", false);
    oled_write_ln(led_usb_state.num_lock ? " yes" : " no", false);

    return false;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        return oled_led_task_user();
    }
    return oled_right_task_user();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        if (is_keyboard_master()) {
            return rotation;
        }
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_180;
}

#endif
