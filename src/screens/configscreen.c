/*******************************************************************************
 *
 * avr-boy
 * Copyright (C) 2020 Matthias Escher
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#include "configscreen.h"

#include <stdint.h>

#include "display/font5x7.h"
#include "display/graphx.h"

#define X_LEFT_PADDING 10

#define X_KEY_START      8
#define X_VALUE_START    104
#define Y_KEYVALUE_START 16
#define Y_DELTA          8

#define INDEX_MAX

static uint8_t cursor[2][5] = {{0x00, 0xfE, 0x7C, 0x38, 0x10},
                               {0x00, 0x7F, 0x3E, 0x1C, 0x08}};

static void draw_keyvalue(uint8_t index, const char *key, const char *value)
{
	uint8_t y = Y_KEYVALUE_START + (Y_DELTA * index);

	graphx_puts(&font5x7, X_KEY_START, y, key);
	graphx_puts(&font5x7, X_VALUE_START, y, value);
}

static uint8_t get_index(uint8_t current_index, c_buttonstat_t *buttons)
{
	if (core_button_get(buttons, BUTTON_UP))
		current_index--;
	if (core_button_get(buttons, BUTTON_DOWN))
		current_index++;

	return current_index;
}

uint8_t *cursor_tile()
{
	static uint8_t toggle = 0;

	if (toggle) {
		toggle = 0;
		return &cursor[0][0];
	}
	else {
		toggle = 1;
		return &cursor[1][0];
	}
}

static void draw_cursor(uint8_t index)
{
	static uint8_t old_index = 0;

	//	if (old_index != index) {
	graphx_puts(&font5x7, 0, Y_KEYVALUE_START + (Y_DELTA * old_index), " ");

	graphx_draw_tile(0, Y_KEYVALUE_START + (Y_DELTA * index), cursor_tile(),
	                 5, 8);

	old_index = index;
	//	}
}

void menuconfig_refresh(c_buttonstat_t *buttons)
{

	static uint8_t current_index = 0;

	graphx_puts(&font5x7, 16, 0, "configuration");
	graphx_draw_hline(5, 127 - 5, 10, GRAPHX_PIXEL_ON);

	current_index = get_index(current_index, buttons);
	draw_cursor(current_index);

	draw_keyvalue(0, "Backlight", "+255");
	draw_keyvalue(1, "Test Buttons", "");
}
