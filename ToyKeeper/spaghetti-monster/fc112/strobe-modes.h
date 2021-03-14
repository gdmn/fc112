/*
 * strobe-modes.h: Strobe modes for Anduril.
 *
 * Copyright (C) 2017 Selene Scriven
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef STROBE_MODES_H
#define STROBE_MODES_H

// full FET strobe can be a bit much...  use max regulated level instead,
// if there's a bright enough regulated level
#ifndef STROBE_BRIGHTNESS
#ifdef MAX_Nx7135
#define STROBE_BRIGHTNESS MAX_Nx7135
#else
#define STROBE_BRIGHTNESS MAX_LEVEL
#endif
#endif

#ifdef USE_STROBE_STATE
uint8_t strobe_state(Event event, uint16_t arg);
inline void strobe_state_iter();
#endif

// bike mode config options
#ifdef USE_BIKE_FLASHER_MODE
#define MAX_BIKING_LEVEL 120  // should be 127 or less
uint8_t bike_flasher_brightness = MAX_1x7135;
inline void bike_flasher_iter();
#endif

#endif
