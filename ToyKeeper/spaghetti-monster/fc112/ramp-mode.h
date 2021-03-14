/*
 * ramp-mode.h: Ramping functions for Anduril.
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

#ifndef RAMP_MODE_H
#define RAMP_MODE_H

#ifndef RAMP_LENGTH
#define RAMP_LENGTH 150  // default, if not overridden in a driver cfg file
#endif

// thermal properties, if not defined per-driver
#ifndef MIN_THERM_STEPDOWN
#define MIN_THERM_STEPDOWN MAX_1x7135  // lowest value it'll step down to
#endif
#ifndef THERM_FASTER_LEVEL
    #ifdef MAX_Nx7135
    #define THERM_FASTER_LEVEL MAX_Nx7135  // throttle back faster when high
    #else
    #define THERM_FASTER_LEVEL (RAMP_SIZE*4/5)  // throttle back faster when high
    #endif
#endif

// configure the timing of turning on/off in regular ramp mode
// press: react as soon as the button is pressed
#define B_PRESS_T 0
// release: react as soon as the button is released
#define B_RELEASE_T 1
// timeout: react as soon as we're sure the user isn't doing a double-click
#define B_TIMEOUT_T 2
// defaults are release on, timeout off
#ifndef B_TIMING_ON
//#define B_TIMING_ON B_PRESS_T
#define B_TIMING_ON B_RELEASE_T
#endif
#ifndef B_TIMING_OFF
//#define B_TIMING_OFF B_RELEASE_T
#define B_TIMING_OFF B_TIMEOUT_T
#endif

// default ramp options if not overridden earlier per-driver
#ifndef RAMP_STYLE
#define RAMP_STYLE 0  // smooth default
#endif
#ifndef RAMP_SMOOTH_FLOOR
  #define RAMP_SMOOTH_FLOOR 1
#endif
#ifndef RAMP_SMOOTH_CEIL
  #if PWM_CHANNELS == 3
    #define RAMP_SMOOTH_CEIL MAX_Nx7135
  #else
    #define RAMP_SMOOTH_CEIL MAX_LEVEL - 30
  #endif
#endif
#ifndef RAMP_DISCRETE_FLOOR
  #define RAMP_DISCRETE_FLOOR 20
#endif
#ifndef RAMP_DISCRETE_CEIL
  #define RAMP_DISCRETE_CEIL RAMP_SMOOTH_CEIL
#endif
#ifndef RAMP_DISCRETE_STEPS
  #define RAMP_DISCRETE_STEPS 7
#endif

// ramping mode and its related config mode
uint8_t steady_state(Event event, uint16_t arg);

// calculate the nearest ramp level which would be valid at the moment
// (is a no-op for smooth ramp, but limits discrete ramp to only the
// correct levels for the user's config)
uint8_t nearest_level(int16_t target);

// ensure ramp globals are correct
void ramp_update_config();

#ifdef USE_THERMAL_REGULATION
// brightness before thermal step-down
uint8_t target_level = 0;
void set_level_and_therm_target(uint8_t level);
#else
#define set_level_and_therm_target(level) set_level(level)
#endif


// brightness control
uint8_t memorized_level = DEFAULT_LEVEL;
// smooth vs discrete ramping
uint8_t ramp_style = RAMP_STYLE;  // 0 = smooth, 1 = discrete
// current values, regardless of style
uint8_t ramp_floor = RAMP_SMOOTH_FLOOR;
uint8_t ramp_ceil = RAMP_SMOOTH_CEIL;
// per style
uint8_t ramp_floors[] = {
    RAMP_SMOOTH_FLOOR,
    RAMP_DISCRETE_FLOOR,
    };
uint8_t ramp_ceils[] = {
    RAMP_SMOOTH_CEIL,
    RAMP_DISCRETE_CEIL,
    };
uint8_t ramp_stepss[] = {
    0,
    RAMP_DISCRETE_STEPS,
    };
uint8_t ramp_discrete_step_size;  // don't set this


#endif
