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
#include "driver/i2cmaster.h"
#include "driver/ks0108.h"
#include "driver/pcf8574.h"
#include "driver/uart.h"
#include "graphx.h"
#include "logger.h"
#include "menu-config.h"

static void init(void)
{
	uart_init();
	i2c_init();
	button_init();
	ks0108_init();
	graphx_init();

	LOG_INFO("initialization done!");
}

int main(void)
{
	init();

	struct button buttons;

	bootscreen_show();

	_delay_ms(1000);

	while (1) {
		_delay_ms(10);
		button_read(&buttons);
		button_debug(&buttons);
		menuconfig_refresh(&buttons);
		ks0108_drawgraphx();
	}
}
