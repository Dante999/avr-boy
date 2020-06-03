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
#include "driver/drivers.h"
#include "graphx.h"
#include "lcd.h"
#include "logger.h"
//#include "menu-config.h"
#include "screensaver.h"

static void init(void)
{
	drivers_init();
	button_init();
	graphx_init();
	screensaver_init();

	LOG_INFO("initialization done!");
}

int main(void)
{
	init();

	struct button buttons;

	bootscreen_show();

	while (1) {
		//_delay_ms(10);
		button_read(&buttons);
		button_debug(&buttons);

		screensaver_run(0);

		lcd_drawbuffer(graphx_buffer());
	}
}
