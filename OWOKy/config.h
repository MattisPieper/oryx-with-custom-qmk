/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#undef TAPPING_TERM
#define TAPPING_TERM 175

#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "OWOKy/Ay5wE"
#define LAYER_STATE_8BIT

#define TAPPING_TERM_PER_KEY
#define RGB_MATRIX_STARTUP_SPD 60

#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH


/* Custom QMK Code */

/**
 * Suppress tap-hold mods within a *typing streak* by defining
 * ACHORDION_STREAK. This can help preventing accidental mod
 * activation when performing a fast tapping sequence.
 * This is inspired by https://sunaku.github.io/home-row-mods.html#typing-streaks
 *
 * Enable with:
 *
 *    #define ACHORDION_STREAK
 *
 * Adjust the maximum time between key events before modifiers can be enabled
 * by defining the following callback in your keymap.c:
 *
 *    uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode) {
 *      return 100;  // Default of 100 ms.
 *    }
 */
#ifdef ACHORDION_STREAK
uint16_t achordion_streak_timeout(uint16_t tap_hold_keycode);
#endif

/**
 * Handler function for Achordion.
 *
 * Call this function from `process_record_user()` as
 *
 *     #include "features/achordion.h"
 *
 *     bool process_record_user(uint16_t keycode, keyrecord_t* record) {
 *       if (!process_achordion(keycode, record)) { return false; }
 *       // Your macros...
 *       return true;
 *     }
 */
bool process_achordion(uint16_t keycode, keyrecord_t* record);

/**
 * Matrix task function for Achordion.
 *
 * Call this function from `matrix_scan_user()` as
 *
 *     void matrix_scan_user(void) {
 *       achordion_task();
 *     }
 */
void achordion_task(void);

/**
 * Optional callback to customize which key chords are considered "held".
 *
 * In your keymap.c, define the callback
 *
 *     bool achordion_chord(uint16_t tap_hold_keycode,
 *                          keyrecord_t* tap_hold_record,
 *                          uint16_t other_keycode,
 *                          keyrecord_t* other_record) {
 *        // Conditions...
 *     }
 *
 * This callback is called if while `tap_hold_keycode` is pressed,
 * `other_keycode` is pressed. Return true if the tap-hold key should be
 * considered held, or false to consider it tapped.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @param tap_hold_record keyrecord_t from the tap-hold press event.
 * @param other_keycode Keycode of the other key.
 * @param other_record keyrecord_t from the other key's press event.
 * @return True if the tap-hold key should be considered held.
 */
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record);

/**
 * Optional callback to define a timeout duration per keycode.
 *
 * In your keymap.c, define the callback
 *
 *     uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
 *       // ...
 *     }
 *
 * The callback determines Achordion's timeout duration for `tap_hold_keycode`
 * in units of milliseconds. The timeout be in the range 0 to 32767 ms (upper
 * bound is due to 16-bit timer limitations). Use a timeout of 0 to bypass
 * Achordion.
 *
 * @param tap_hold_keycode Keycode of the tap-hold key.
 * @return Timeout duration in milliseconds in the range 0 to 32767.
 */
uint16_t achordion_timeout(uint16_t tap_hold_keycode);

/**
 * Optional callback defining which mods are "eagerly" applied.
 *
 * This callback defines  which mods are "eagerly" applied while a mod-tap
 * key is still being settled. This is helpful to reduce delay particularly when
 * using mod-tap keys with an external mouse.
 *
 * Define this callback in your keymap.c. The default callback is eager for
 * Shift and Ctrl, and not for Alt and GUI:
 *
 *     bool achordion_eager_mod(uint8_t mod) {
 *       return (mod & (MOD_LALT | MOD_LGUI)) == 0;
 *     }
 *
 * @note `mod` should be compared with `MOD_` prefixed codes, not `KC_` codes,
 * described at <https://docs.qmk.fm/#/mod_tap>.
 *
 * @param mod Modifier `MOD_` code.
 * @return True if the modifier should be eagerly applied.
 */
bool achordion_eager_mod(uint8_t mod);

/**
 * Returns true if the args come from keys on opposite hands.
 *
 * @param tap_hold_record keyrecord_t from the tap-hold key's event.
 * @param other_record keyrecord_t from the other key's event.
 * @return True if the keys are on opposite hands.
 */
bool achordion_opposite_hands(const keyrecord_t* tap_hold_record,
                              const keyrecord_t* other_record);
