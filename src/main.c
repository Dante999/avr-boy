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
#include <avr/io.h>

#include "button.h"
#include "i2cmaster.h"
#include "pcf8574.h"
#include "uart.h"
#include <util/delay.h>

static void init(void)
{
	i2c_init();
	uart_init();
}

static void debug_buttons(void)
{
	static struct Button button;

	button_read(&button);

	if (button.reg0 & BUTTON_REG0_UP) {
		uart_puts("BUTTON_UP ");
	}

	if (button.reg0 & BUTTON_REG0_DOWN) {
		uart_puts("BUTTON_DOWN ");
	}

	if (button.reg0 & BUTTON_REG0_LEFT) {
		uart_puts("BUTTON_LEFT ");
	}

	if (button.reg0 & BUTTON_REG0_RIGHT) {
		uart_puts("BUTTON_RIGHT ");
	}

	if (button.reg0 & BUTTON_REG0_A) {
		uart_puts("BUTTON_A ");
	}

	if (button.reg0 & BUTTON_REG0_B) {
		uart_puts("BUTTON_B ");
	}

	if (button.reg0 & BUTTON_REG0_START) {
		uart_puts("BUTTON_START ");
	}

	if (button.reg0 & BUTTON_REG0_SELECT) {
		uart_puts("BUTTON_SELECT ");
	}

	if (button.reg1 & BUTTON_REG1_CONFIG) {
		uart_puts("BUTTON_CONFIG ");
	}

	uart_putsln("");
}

int main(void)
{
	init();

	uart_putsln("initialization done!");

	button_init();

	while (1) {
		_delay_ms(100);

		debug_buttons();
	}
}
