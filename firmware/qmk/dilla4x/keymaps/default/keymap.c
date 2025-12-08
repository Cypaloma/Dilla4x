/* Copyright 2025 Dilla4x Community
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Grid (Web-Dilla4x Compatible)
     * Row 0 (Top):    1   2   3   4
     * Row 1:          Q   W   E   R
     * Row 2:          A   S   D   F
     * Row 3 (Bottom): Z   X   C   V
     * 
     * This layout maps perfectly to the Web-Dilla4x sampler defaults
     * and works as a standard macropad out of the box.
     */
    [0] = LAYOUT_ortho_4x4(
        KC_1, KC_2, KC_3, KC_4,
        KC_Q, KC_W, KC_E, KC_R,
        KC_A, KC_S, KC_D, KC_F,
        KC_Z, KC_X, KC_C, KC_V
    )
};
