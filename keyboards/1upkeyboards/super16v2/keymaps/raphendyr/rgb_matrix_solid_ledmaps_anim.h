#ifdef ENABLE_RGB_MATRIX_SOLID_LEDMAPS
RGB_MATRIX_EFFECT(SOLID_LEDMAPS)
# ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#  include "quantum/action_layer.h"

extern const HSV ledmaps[][RGB_MATRIX_LED_COUNT];

bool SOLID_LEDMAPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // the 1 ensures leds never turn off
    uint8_t val = qadd8(rgb_matrix_get_val(), 1);
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    const HSV *ledmap = ledmaps[layer];

    for (uint8_t i = led_min; i < led_max; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[i].h),
            .s = pgm_read_byte(&ledmap[i].s),
            .v = pgm_read_byte(&ledmap[i].v),
        };
#  ifdef RGB_MATRIX_SOLID_LEDMAPS_UNDERGLOW_BRIGHTNESS
        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
            hsv.v = RGB_MATRIX_SOLID_LEDMAPS_UNDERGLOW_BRIGHTNESS;
        } else {
            hsv.v = scale8_video(hsv.v, val);
        }
#  else
        hsv.v = scale8_video(hsv.v, val);
#  endif
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

# endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // ENABLE_RGB_MATRIX_SOLID_LEDMAPS
