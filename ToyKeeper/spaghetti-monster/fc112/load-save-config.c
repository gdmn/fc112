/*
 * load-save-config.c: Load/save/eeprom functions for Anduril.
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

#ifndef LOAD_SAVE_CONFIG_C
#define LOAD_SAVE_CONFIG_C

#include "load-save-config-fsm.h"
#include "load-save-config.h"

void load_config() {
    if (load_eeprom()) {
        ramp_style = eeprom[ramp_style_e];
        #ifdef USE_BIKE_FLASHER_MODE
        bike_flasher_brightness = eeprom[bike_flasher_brightness_e];
        #endif
        #ifdef USE_BEACON_MODE
        beacon_seconds = eeprom[beacon_seconds_e];
        #endif
        #ifdef USE_THERMAL_REGULATION
        therm_ceil = eeprom[therm_ceil_e];
        therm_cal_offset = eeprom[therm_cal_offset_e];
        #endif
        #ifdef USE_INDICATOR_LED
        indicator_led_mode = eeprom[indicator_led_mode_e];
        #endif
        #ifdef USE_AUX_RGB_LEDS
        rgb_led_off_mode = eeprom[rgb_led_off_mode_e];
        rgb_led_lockout_mode = eeprom[rgb_led_lockout_mode_e];
        #endif
    }
    #ifdef START_AT_MEMORIZED_LEVEL
    if (load_eeprom_wl()) {
        memorized_level = eeprom_wl[0];
    }
    #endif
}

void save_config() {
    eeprom[ramp_style_e] = ramp_style;
    #ifdef USE_BIKE_FLASHER_MODE
    eeprom[bike_flasher_brightness_e] = bike_flasher_brightness;
    #endif
    #ifdef USE_BEACON_MODE
    eeprom[beacon_seconds_e] = beacon_seconds;
    #endif
    #ifdef USE_THERMAL_REGULATION
    eeprom[therm_ceil_e] = therm_ceil;
    eeprom[therm_cal_offset_e] = therm_cal_offset;
    #endif
    #ifdef USE_INDICATOR_LED
    eeprom[indicator_led_mode_e] = indicator_led_mode;
    #endif
    #ifdef USE_AUX_RGB_LEDS
    eeprom[rgb_led_off_mode_e] = rgb_led_off_mode;
    eeprom[rgb_led_lockout_mode_e] = rgb_led_lockout_mode;
    #endif

    save_eeprom();
}

#ifdef START_AT_MEMORIZED_LEVEL
void save_config_wl() {
    eeprom_wl[0] = memorized_level;
    save_eeprom_wl();
}
#endif


#endif

