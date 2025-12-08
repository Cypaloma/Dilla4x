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
     * Row 0 (top):    C3  C#3 D3  D#3  (MIDI 48-51)
     * Row 1:          G#2 A2  A#2 B2   (MIDI 44-47)
     * Row 2:          E2  F2  F#2 G2   (MIDI 40-43)
     * Row 3 (bottom): C2  C#2 D2  D#2  (MIDI 36-39)
     */
    [0] = LAYOUT_ortho_4x4(
        MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3,  // C3-D#3 (MIDI 48-51)
        MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,   // G#2-B2 (MIDI 44-47)
        MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2,   // E2-G2  (MIDI 40-43)
        MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2   // C2-D#2 (MIDI 36-39)
    )
};
