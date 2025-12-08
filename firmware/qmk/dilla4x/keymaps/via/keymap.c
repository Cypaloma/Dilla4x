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
    /* Layer 0: MIDI Notes (matches Dilla4x-MIDI firmware)
     * Chromatic scale C2 (36) to D#3 (51)
     * 
     * VIA v3 supports dynamic layer configuration - additional layers
     * can be added via the VIA configurator as needed
     */
    [0] = LAYOUT_ortho_4x4(
        MI_C3,  MI_Cs3, MI_D3,  MI_Ds3,  // C3-D#3 (MIDI 48-51)
        MI_Gs2, MI_A2,  MI_As2, MI_B2,   // G#2-B2 (MIDI 44-47)
        MI_E2,  MI_F2,  MI_Fs2, MI_G2,   // E2-G2  (MIDI 40-43)
        MI_C2,  MI_Cs2, MI_D2,  MI_Ds2   // C2-D#2 (MIDI 36-39)
    )
};
