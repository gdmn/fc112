/*
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

#ifndef MOON_MODE_C
#define MOON_MODE_C

#include "moon-mode.h"

uint8_t moon_mode_state(Event event, uint16_t arg) {
    // ramp_style == true ==> discrete mode

    #if (B_TIMING_OFF == B_RELEASE_T)
    // if the user double clicks, we need to abort turning off,
    // and this stores the level to return to
    static uint8_t level_before_off = 0;
    #endif

    uint8_t mode_min = ramp_floors[0];
    if (ramp_floors[1] < mode_min) mode_min = ramp_floors[1];

    // turn LED on when we first enter the mode
    if ((event == EV_enter_state) || (event == EV_reenter_state)) {
        arg = mode_min;
        set_level_and_therm_target(arg);
        return MISCHIEF_MANAGED;
    }

    #if (B_TIMING_OFF == B_RELEASE_T)
    // 1 click (early): off, if configured for early response
    else if (event == EV_click1_release) {
        level_before_off = actual_level;
        set_level_and_therm_target(0);
        return MISCHIEF_MANAGED;
    }
    // 2 clicks (early): abort turning off, if configured for early response
    else if (event == EV_click2_press) {
        set_level_and_therm_target(level_before_off);
        return MISCHIEF_MANAGED;
    }
    #endif  // if (B_TIMING_OFF == B_RELEASE_T)

    // 1 click: off
    else if (event == EV_1click) {
        set_state(off_state, 0);
        return MISCHIEF_MANAGED;
    }

    // 2 clicks: go to highest level
    else if (event == EV_2clicks) {
        memorized_level = ramp_ceil;
        set_state(steady_state, MAX_LEVEL); // goes to ramp ceil
        return MISCHIEF_MANAGED;
    }

    #ifdef USE_LOCKOUT_MODE
    // 4 clicks: shortcut to lockout mode
    else if (event == EV_4clicks) {
        set_level(0);
        set_state(lockout_state, 0);
        return MISCHIEF_MANAGED;
    }
    #endif

    // hold: change brightness (brighter, dimmer)
    // click, hold: change brightness (dimmer)
    else if ((event == EV_click1_hold)) {
        // ramp slower in discrete mode
        if (arg % HOLD_TIMEOUT != 0) {
            return MISCHIEF_MANAGED;
        }

// $ ./build-all.sh
// $ ../../../bin/flash-tiny1634.sh hex/fc112.emisar-d4v2.hex

        set_state(steady_state, 1);
        return MISCHIEF_MANAGED;
    }

    // 3 clicks: toggle smooth vs discrete ramping
    else if (event == EV_3clicks) {
        ramp_style = !ramp_style;
        save_config();
        #ifdef START_AT_MEMORIZED_LEVEL
        save_config_wl();
        #endif
        blip();
        memorized_level = nearest_level(actual_level);
        set_state(steady_state, memorized_level);
        return MISCHIEF_MANAGED;
    }

    return EVENT_NOT_HANDLED;
}

#endif
