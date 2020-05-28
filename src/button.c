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

#include "driver/pcf8574.h"
#include <stdint.h>

#include "logger.h"

#define ROW0 (1 << 7)
#define ROW1 (1 << 6)
#define ROW2 (1 << 5)
#define COL0 (1 << 4)
#define COL1 (1 << 3)
#define COL2 (1 << 2)

static uint8_t reg = 0xFF;

static void read_col0(struct button *button, uint8_t col0)
{
	if (col0 & ROW0)
		button->reg0 |= BUTTON_REG0_UP;

	if (col0 & ROW1)
		button->reg0 |= BUTTON_REG0_DOWN;

	if (col0 & ROW2)
		button->reg0 |= BUTTON_REG0_START;
}

static void read_col1(struct button *button, uint8_t col1)
{
	if (col1 & ROW0)
		button->reg0 |= BUTTON_REG0_RIGHT;

	if (col1 & ROW1)
		button->reg0 |= BUTTON_REG0_B;

	if (col1 & ROW2)
		button->reg0 |= BUTTON_REG0_SELECT;
}

static void read_col2(struct button *button, uint8_t col2)
{
	if (col2 & ROW0)
		button->reg0 |= BUTTON_REG0_LEFT;

	if (col2 & ROW1)
		button->reg0 |= BUTTON_REG0_A;

	if (col2 & ROW2)
		button->reg1 |= BUTTON_REG1_CONFIG;
}

void button_init()
{
	pcf8574_set(reg);
}

void button_read(struct button *button)
{
	button->reg0 = 0x00;
	button->reg1 = 0x00;

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

void button_debug(struct button *buttons)
{
	if (buttons->reg0 & BUTTON_REG0_UP) {
		LOG_INFO("BUTTON_UP ");
	}

	if (buttons->reg0 & BUTTON_REG0_DOWN) {
		LOG_INFO("BUTTON_DOWN ");
	}

	if (buttons->reg0 & BUTTON_REG0_LEFT) {
		LOG_INFO("BUTTON_LEFT ");
	}

	if (buttons->reg0 & BUTTON_REG0_RIGHT) {
		LOG_INFO("BUTTON_RIGHT ");
	}

	if (buttons->reg0 & BUTTON_REG0_A) {
		LOG_INFO("BUTTON_A ");
	}

	if (buttons->reg0 & BUTTON_REG0_B) {
		LOG_INFO("BUTTON_B ");
	}

	if (buttons->reg0 & BUTTON_REG0_START) {
		LOG_INFO("BUTTON_START ");
	}

	if (buttons->reg0 & BUTTON_REG0_SELECT) {
		LOG_INFO("BUTTON_SELECT ");
	}

	if (buttons->reg1 & BUTTON_REG1_CONFIG) {
		LOG_INFO("BUTTON_CONFIG ");
	}
}
