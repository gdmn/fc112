/*
 * Anduril: Narsil-inspired UI for SpaghettiMonster.
 * (Anduril is Aragorn's sword, the blade Narsil reforged)
 *
 * Copyright (C) 2017-2020 Selene Scriven
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

/*
 * Usually a program would be structured like this...
 * - Library headers
 * - App headers
 * - App code
 *
 * ... in each source file.
 * ... and each library and part of the program would be linked together.
 *
 * But this doesn't follow that pattern, because it's using the
 *   -fwhole-program
 * flag to reduce the compiled size.  It lets us fit more features
 * in a tiny MCU chip's ROM.
 *
 * So the structure is like this instead...
 * - App-level configuration headers
 *   - Default config
 *   - Per build target config
 * - Library-level configuration headers
 * - Library code (FSM itself)
 * - App headers
 * - App code (all of it, inline)
 *
 * Don't do this in regular programs.  It's weird and kind of gross.
 * But in this case it gives us a bunch of much-needed space, so... woot.
 *
 * Also, there are a ton of compile-time options because it needs to build
 * a bunch of different versions and each one needs to be trimmed as small
 * as possible.  These are mostly "USE" flags.
 */

/********* User-configurable options *********/
#include "config-default.h"

/********* specific settings for known driver types *********/
// Anduril config file name (set it here or define it at the gcc command line)
//#define CONFIGFILE cfg-blf-q8.h

#include "tk.h"
#include incfile(CONFIGFILE)


/********* Include headers which need to be before FSM *********/

// enable FSM features needed by basic ramping functions
#include "ramp-mode-fsm.h"

#ifdef USE_BATTCHECK_MODE
#include "battcheck-mode-fsm.h"
#endif

#ifdef USE_LOCKOUT_MODE
#include "lockout-mode-fsm.h"
#endif

// enable FSM features needed by strobe modes
#include "strobe-modes-fsm.h"

// figure out how many bytes of eeprom are needed,
// based on which UI features are enabled
// (include this one last)
#include "load-save-config-fsm.h"


/********* bring in FSM / SpaghettiMonster *********/
#define USE_IDLE_MODE  // reduce power use while awake and no tasks are pending

#include "spaghetti-monster.h"

/********* does this build target have special code to include? *********/
#ifdef OVERRIDES_FILE
#include incfile(OVERRIDES_FILE)
#endif


/********* Include all the regular app headers *********/

#include "off-mode.h"
#include "ramp-mode.h"
#include "load-save-config.h"
#include "config-mode.h"
#include "aux-leds.h"
#include "misc.h"

#ifdef USE_BATTCHECK_MODE
#include "battcheck-mode.h"
#endif

#ifdef USE_BEACON_MODE
#include "beacon-mode.h"
#endif

#ifdef USE_LOCKOUT_MODE
#include "lockout-mode.h"
#endif

// this one detects its own enable/disable settings
#include "strobe-modes.h"

/********* Include all the app logic source files *********/
// (is a bit weird to do things this way,
//  but it saves a lot of space by letting us use the -fwhole-program flag)

#include "off-mode.c"
#include "ramp-mode.c"
#include "load-save-config.c"
#include "config-mode.c"
#include "aux-leds.c"
#include "misc.c"

#ifdef USE_BATTCHECK_MODE
#include "battcheck-mode.c"
#endif

#ifdef USE_BEACON_MODE
#include "beacon-mode.c"
#endif

#ifdef USE_LOCKOUT_MODE
#include "lockout-mode.c"
#endif

#ifdef USE_STROBE_STATE
#include "strobe-modes.c"
#endif

#ifdef USE_SOS_MODE
#include "sos-mode.c"
#endif


// runs one time at boot, when power is connected
void setup() {

    #ifndef START_AT_MEMORIZED_LEVEL

        // regular e-switch light, no hard clicky power button

        // blink at power-on to let user know power is connected
        blink_once();

        load_config();

        push_state(off_state, 1);

    #else  // if START_AT_MEMORIZED_LEVEL

        // dual switch: e-switch + power clicky
        // power clicky acts as a momentary mode
        load_config();

        if (button_is_pressed())
            // hold button to go to moon
            push_state(steady_state, 1);
        else
            // otherwise use memory
            push_state(steady_state, memorized_level);

    #endif  // ifdef START_AT_MEMORIZED_LEVEL

}


// runs repeatedly whenever light is "on" (not in standby)
void loop() {

    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;

    #ifdef USE_AUX_RGB_LEDS_WHILE_ON
    // display battery charge on RGB button during use
    if (! setting_rgb_mode_now) rgb_led_voltage_readout(1);
    #endif

    if (0) {}  // placeholder

    #ifdef USE_STROBE_STATE
    else if ((state == strobe_state)) {
        strobe_state_iter();
    }
    #endif  // #ifdef USE_STROBE_STATE

    #ifdef USE_BATTCHECK
    else if (state == battcheck_state) {
        battcheck();
    }
    #endif

    #ifdef USE_BEACON_MODE
    else if (state == beacon_state) {
        beacon_mode_iter();
    }
    #endif

    #ifdef USE_IDLE_MODE
    else {
        // doze until next clock tick
        idle_mode();
    }
    #endif

}


// instead of handling EV_low_voltage in each mode,
// it's handled globally here to make the code smaller and simpler
void low_voltage() {

    // "current_state" is volatile, so cache it to reduce code size
    StatePtr state = current_state;

    // TODO: turn off aux LED(s) when power is really low

    if (0) {}  // placeholder

    #ifdef USE_STROBE_STATE
    // "step down" from strobe to something low
    else if (state == strobe_state) {
        set_state(steady_state, RAMP_SIZE/6);
    }
    #endif

    // in normal mode, step down or turn off
    else if (state == steady_state) {
        if (actual_level > 1) {
            uint8_t lvl = (actual_level >> 1) + (actual_level >> 2);
            set_level_and_therm_target(lvl);
        }
        else {
            set_state(off_state, 0);
        }
    }
    // all other modes, just turn off when voltage is low
    else {
        set_state(off_state, 0);
    }

}
