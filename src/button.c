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
#include "button.h"

#include <stdint.h>

#include "driver/pcf8574.h"
#include "protocol/core.h"
#include "util/logger.h"

#define ROW0 (1 << 7)
#define ROW1 (1 << 6)
#define ROW2 (1 << 5)
#define COL0 (1 << 4)
#define COL1 (1 << 3)
#define COL2 (1 << 2)

static uint8_t reg = 0xFF;

static void read_col0(struct button_stat *button, uint8_t col0)
{
	if (col0 & ROW0)
		core_button_set(button, BUTTON_UP);

	if (col0 & ROW1)
		core_button_set(button, BUTTON_DOWN);

	if (col0 & ROW2)
		core_button_set(button, BUTTON_START);
}

static void read_col1(struct button_stat *button, uint8_t col1)
{
	if (col1 & ROW0)
		core_button_set(button, BUTTON_RIGHT);

	if (col1 & ROW1)
		core_button_set(button, BUTTON_B);

	if (col1 & ROW2)
		core_button_set(button, BUTTON_SELECT);
}

static void read_col2(struct button_stat *button, uint8_t col2)
{
	if (col2 & ROW0)
		core_button_set(button, BUTTON_LEFT);

	if (col2 & ROW1)
		core_button_set(button, BUTTON_A);

	if (col2 & ROW2)
		core_button_set(button, BUTTON_CONFIG);
}

void button_init()
{
	pcf8574_set(reg);
}

void button_read(struct button_stat *button)
{

	core_button_clear(button);

	pcf8574_set(reg & ~COL0);
	uint8_t col0 = ~pcf8574_get();

	pcf8574_set(reg & ~COL1);
	uint8_t col1 = ~pcf8574_get();

	pcf8574_set(reg & ~COL2);
	uint8_t col2 = ~pcf8574_get();

	read_col0(button, col0);
	read_col1(button, col1);
	read_col2(button, col2);
}

void button_debug(struct button_stat *button)
{
	if (core_button_get(button, BUTTON_UP)) {
		LOG_INFO("BUTTON_UP ");
	}

	if (core_button_get(button, BUTTON_DOWN)) {
		LOG_INFO("BUTTON_DOWN ");
	}

	if (core_button_get(button, BUTTON_LEFT)) {
		LOG_INFO("BUTTON_LEFT ");
	}

	if (core_button_get(button, BUTTON_RIGHT)) {
		LOG_INFO("BUTTON_RIGHT ");
	}

	if (core_button_get(button, BUTTON_A)) {
		LOG_INFO("BUTTON_A ");
	}

	if (core_button_get(button, BUTTON_B)) {
		LOG_INFO("BUTTON_B ");
	}

	if (core_button_get(button, BUTTON_START)) {
		LOG_INFO("BUTTON_START ");
	}

	if (core_button_get(button, BUTTON_SELECT)) {
		LOG_INFO("BUTTON_SELECT ");
	}

	if (core_button_get(button, BUTTON_CONFIG)) {
		LOG_INFO("BUTTON_CONFIG ");
	}
}
