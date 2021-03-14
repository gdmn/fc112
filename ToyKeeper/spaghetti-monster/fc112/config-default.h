/*
 * config-default.h: Default configuration for Anduril.
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

#ifndef CONFIG_DEFAULT_H
#define CONFIG_DEFAULT_H

/*
 * This file specifies the default settings for Anduril.
 *
 * These settings can be overridden per build target, in cfg-*.h files...
 * ... but most are not.  So changing one here will make it change in
 * almost every build target.
 *
 * Some configurable settings are also in other *.h files.
 */

/********* User-configurable options *********/
// low voltage protection (also required for battery check mode)
#define USE_LVP

// overheat protection
#define USE_THERMAL_REGULATION
#define DEFAULT_THERM_CEIL 45  // try not to get hotter than this (in C)

///// Ramp mode options /////

// button timing for turning light on/off:
// B_PRESS_T:   activate as soon as button is pressed
// B_RELEASE_T: activate when user lets go of button
// B_TIMEOUT_T: activate when we're sure the user won't double-click
// defaults are release on, timeout off
#define B_TIMING_ON B_RELEASE_T
#define B_TIMING_OFF B_TIMEOUT_T

// default ramp style: 0 = smooth, 1 = stepped
#define RAMP_STYLE 0

// short blip when crossing from "click" to "hold" from off
// (helps the user hit moon mode exactly, instead of holding too long
//  or too short)
#define MOON_TIMING_HINT  // only applies if B_TIMING_ON == B_PRESS_T
//#define BLINK_AT_RAMP_FLOOR
#define BLINK_AT_RAMP_CEIL

///// extra modes (enable / disable / configure each mode) /////

// enable the battery check mode (shows remaining charge) (requires USE_LVP)
#define USE_BATTCHECK_MODE
// battery readout style (pick one)
// TODO: allow VpT and 4-bar simultaneously,
//       so one can be in "simple mode" and the other in "advanced mode"
//#define BATTCHECK_VpT
//#define BATTCHECK_8bars  // FIXME: breaks build
#define BATTCHECK_4bars  // FIXME: breaks build

// enable beacon mode
#define USE_BEACON_MODE

// enable/disable various strobe modes
#define USE_BIKE_FLASHER_MODE

// enable a mode for locking the light for safe carry
#define USE_LOCKOUT_MODE
// should lockout mode function as a momentary moon mode?
#define USE_MOON_DURING_LOCKOUT_MODE

// cut clock speed at very low modes for better efficiency
// (defined here so config files can override it)
#define USE_DYNAMIC_UNDERCLOCKING

#define USE_PSEUDO_RAND

#endif
