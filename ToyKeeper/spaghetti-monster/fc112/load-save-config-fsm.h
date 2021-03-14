/*
 * load-save-config-fsm.h: FSM config for eeprom configuration in Anduril.
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

#ifndef LOAD_SAVE_CONFIG_FSM_H
#define LOAD_SAVE_CONFIG_FSM_H

// auto-detect how many eeprom bytes
#define USE_EEPROM
typedef enum {
    ramp_style_e,
    #ifdef USE_BIKE_FLASHER_MODE
    bike_flasher_brightness_e,
    #endif
    #ifdef USE_BEACON_MODE
    beacon_seconds_e,
    #endif
    #ifdef USE_THERMAL_REGULATION
    therm_ceil_e,
    therm_cal_offset_e,
    #endif
    #ifdef USE_INDICATOR_LED
    indicator_led_mode_e,
    #endif
    #ifdef USE_AUX_RGB_LEDS
    rgb_led_off_mode_e,
    rgb_led_lockout_mode_e,
    #endif
    eeprom_indexes_e_END
} eeprom_indexes_e;
#define EEPROM_BYTES eeprom_indexes_e_END

#ifdef START_AT_MEMORIZED_LEVEL
#define USE_EEPROM_WL
#define EEPROM_WL_BYTES 1
#endif


#endif
