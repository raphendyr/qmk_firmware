/* Copyright 2022 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "rgb_matrix.h"

# define OFF    { HSV_OFF }
# define AZURE  { HSV_AZURE }
# define BLACK  { HSV_BLACK }
# define BLUE   { HSV_BLUE }
# define CHART  { HSV_CHARTREUSE }
# define CORAL  { HSV_CORAL }
# define CYAN   { HSV_CYAN }
# define GOLD   { HSV_GOLD }
# define GOLDEN { HSV_GOLDENROD }
# define GREEN  { HSV_GREEN }
# define MAGENT { HSV_MAGENTA }
# define ORANGE { HSV_ORANGE }
# define PINK   { HSV_PINK }
# define PURPLE { HSV_PURPLE }
# define RED    { HSV_RED }
# define SPRING { HSV_SPRINGGREEN }
# define TEAL   { HSV_TEAL }
# define TURQ   { HSV_TURQUOISE }
# define WHITE  { HSV_WHITE }
# define YELLOW { HSV_YELLOW }

// clang-format off
# define RGB_MATRIX_LAYOUT_SUPERV2( \
        k00, k01, k02, k03, \
        k10, k11, k12, k13, \
        k20, k21, k22, k23, \
        k30, k31, k32, k33, \
        ug1, ug2, \
        ug3, ug4 \
    ) \
    { \
        k03, k02, k01, k00, \
        k13, k12, k11, k10, \
        k23, k22, k21, k20, \
        k33, k32, k31, k30, \
        ug1, ug2, \
        ug3, ug4 \
    }
// clang-format on

#define KC_MI_MUTE KC_F20

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x4( /* Base */
        KC_MUTE,    KC_MUTE,    KC_MI_MUTE, KC_MI_MUTE,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_NO,      KC_MPRV,    KC_MNXT,
        MO(1),      KC_NO,      KC_MSTP,    KC_MPLY
    ),

    [1] = LAYOUT_ortho_4x4( /* Fn Layer */
        KC_NO,      KC_NO,      QK_BOOT,    KC_NO,
        RGB_TOG,    RGB_HUI,    RGB_SAI,    RGB_VAI,
        RGB_MOD,    RGB_HUD,    RGB_SAD,    RGB_VAD,
        KC_TRNS,    RGB_SPD,    RGB_SPI,    KC_NO
    ),
};

const HSV PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT] = {
    [0] = RGB_MATRIX_LAYOUT_SUPERV2(
        OFF,        GOLD,       GOLD,       OFF,
        OFF,        OFF,        OFF,        OFF,
        OFF,        OFF,        BLUE,       BLUE,
        YELLOW,     OFF,        ORANGE,     GREEN,

        BLUE,       BLUE,
        BLUE,       BLUE
    ),

    [1] = RGB_MATRIX_LAYOUT_SUPERV2(
        OFF,        OFF,        RED,        OFF,
        GREEN,      TURQ,       CORAL,      SPRING,
        MAGENT,     TURQ,       CORAL,      SPRING,
        YELLOW,     GOLD,       GOLD,       OFF,

        PURPLE,     PURPLE,
        PURPLE,     PURPLE
    ),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    switch (layer) {
        case 1: {
            if (index == 0) { /* First encoder */
                if (clockwise) {
                    rgb_matrix_increase_hue();
                } else {
                    rgb_matrix_decrease_hue();
                }
            } else if (index == 1) { /* Second encoder */
                if (clockwise) {
                    rgb_matrix_increase_val();
                } else {

                    rgb_matrix_decrease_val();
                }
            }
            break;
        }
        default: {
            if (index == 0) { /* First encoder */
                if (clockwise) {
                    tap_code_delay(KC_AUDIO_VOL_UP, 10);
                } else {
                    tap_code_delay(KC_AUDIO_VOL_DOWN, 10);
                }
            } else if (index == 1) { /* Second encoder */
                if (clockwise) {
                    tap_code_delay(KC_BRIGHTNESS_UP, 10);
                } else {
                    tap_code_delay(KC_BRIGHTNESS_DOWN, 10);
                }
            }
        }
    }
    return false;
}
#endif  // ENCODER_ENABLE
