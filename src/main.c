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
#include <string.h> // memset(..)
#include <util/delay.h>

#include "bootscreen.h"
#include "button.h"
#include "font8x8.h"
#include "graphx.h"
#include "i2cmaster.h"
#include "ks0108.h"
#include "menu-config.h"
#include "pcf8574.h"
#include "uart.h"

static void init(void)
{
	i2c_init();
	uart_init();
	button_init();
	ks0108_init();

	uart_putsln("initialization done!");
}

static void debug_buttons(struct button *buttons)
{

	button_read(buttons);

	if (buttons->reg0 & BUTTON_REG0_UP) {
		uart_putsln("BUTTON_UP ");
	}

	if (buttons->reg0 & BUTTON_REG0_DOWN) {
		uart_putsln("BUTTON_DOWN ");
	}

	if (buttons->reg0 & BUTTON_REG0_LEFT) {
		uart_putsln("BUTTON_LEFT ");
	}

	if (buttons->reg0 & BUTTON_REG0_RIGHT) {
		uart_putsln("BUTTON_RIGHT ");
	}

	if (buttons->reg0 & BUTTON_REG0_A) {
		uart_putsln("BUTTON_A ");
	}

	if (buttons->reg0 & BUTTON_REG0_B) {
		uart_putsln("BUTTON_B ");
	}

	if (buttons->reg0 & BUTTON_REG0_START) {
		uart_putsln("BUTTON_START ");
	}

	if (buttons->reg0 & BUTTON_REG0_SELECT) {
		uart_putsln("BUTTON_SELECT ");
	}

	if (buttons->reg1 & BUTTON_REG1_CONFIG) {
		uart_putsln("BUTTON_CONFIG ");
	}
}

int main(void)
{
	init();

	struct graphxdata *gd = graphx_new(128, 64);
	struct button      buttons;

	bootscreen_show(gd);

	_delay_ms(1000);

	while (1) {
		_delay_ms(10);
		// menuconfig_refresh(gd, &buttons);
		debug_buttons(&buttons);

		// ks0108_drawgraphx(gd);
	}
}
