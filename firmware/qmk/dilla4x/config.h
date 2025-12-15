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

#pragma once

/* 
 * Modern QMK uses info.json for USB, matrix, and debounce configuration.
 * This file only contains settings that CANNOT be defined in info.json.
 */


/*
 * MIDI Options
 * Using BASIC mode for simple Note On/Off (no velocity sensitivity needed)
 */
#define MIDI_BASIC
