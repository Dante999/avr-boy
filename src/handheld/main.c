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

#include "button.h"
#include "display/graphx.h"
#include "display/lcd.h"
#include "display/sprite.h"
#include "driver/drivers.h"
#include "driver/spislave.h"
#include "core/core.h"
#include "core/handheld.h"
#include "screens/bootscreen.h"
#include "screens/configscreen.h"
#include "screens/screensaver.h"
#include "userport.h"
#include "util/logger.h"

enum state { STATE_SCREENSAVER, STATE_CONFIGMENU, STATE_CARTRIDGE };

#define DDRX_READY  DDRD
#define PORTX_READY PORTD
#define BIT_READY   (1 << PD5)

static void cb_transmit(char c)
{
	spi_transceive(c);
}

static char cb_receive(void)
{
	return spi_transceive(PRTCL_CMD_ACK);
}

static void cb_before_communicate(void)
{
	PORTX_READY |= BIT_READY;
}

static void cb_after_communicate(void)
{
	PORTX_READY &= ~BIT_READY;
}

static void init(void)
{
	drivers_init();
	button_init();
	graphx_init();
	screensaver_init();
	lcd_init();
	userport_init();
	sprite_init();

	// set as output
	DDRX_READY |= BIT_READY;

	handheld_init(cb_transmit, cb_receive);
	handheld_set_cb_before_communicate(cb_before_communicate);
	handheld_set_cb_after_communicate(cb_after_communicate);


	LOG_INFO("initialization done!");
}

int main(void)
{
	init();

	enum state     system_state = STATE_CARTRIDGE;
	c_buttonstat_t buttons;

	bootscreen_show();

	while (1) {
		handheld_wait_for_actions();

		button_read(&buttons);
		button_debug(&buttons);

		switch (system_state) {

		case STATE_CARTRIDGE:
			break;

		case STATE_SCREENSAVER:
			screensaver_run(0);

			if (core_button_get(&buttons, BUTTON_CONFIG)) {
				system_state = STATE_CONFIGMENU;
				graphx_fill_pattern(0x00);
			}

			break;
		case STATE_CONFIGMENU:
			menuconfig_refresh(&buttons);

			if (core_button_get(&buttons, BUTTON_CONFIG)) {
				system_state = STATE_SCREENSAVER;
				graphx_fill_pattern(0x00);
			}

			break;
		}
	}
}
