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
#include "display/graphx.h"
#include "display/lcd.h"
#include "driver/drivers.h"
#include "driver/spislave.h"
#include "driver/uart.h"
#include "logger.h"
#include "menu-config.h"
#include "protocol/handheld.h"
#include "screensaver.h"

enum state { STATE_SCREENSAVER, STATE_CONFIGMENU };

static void cb_transmit(char c)
{
	spi_transceive(c);
}

static char cb_receive(void)
{
	return spi_transceive(CMD_ACK);
}

static void init(void)
{
	drivers_init();
	button_init();
	graphx_init();
	screensaver_init();

	handheld_init(cb_transmit, cb_receive);

	LOG_INFO_LINE("initialization done!");
}

int main(void)
{
	init();

	enum state    system_state = STATE_SCREENSAVER;
	struct button buttons;

	bootscreen_show();

	while (1) {

		handheld_wait_for_actions();

		// uart_puts("Wait SPI... ");
		// uint8_t d = spi_transceive(0x00);

		// uart_putui(d);
		// uart_putsln("");

		// LOG_INFO_UI8(d);
		// LOG_INFO_LINE("");

		//_delay_ms(10);
		button_read(&buttons);
		button_debug(&buttons);

		switch (system_state) {

		case STATE_SCREENSAVER:
			screensaver_run(0);

			if (buttons.reg1 & BUTTON_REG1_CONFIG) {
				system_state = STATE_CONFIGMENU;
				graphx_fill_pattern(0x00);
			}

			break;
		case STATE_CONFIGMENU:
			menuconfig_refresh(&buttons);

			if (buttons.reg1 & BUTTON_REG1_CONFIG) {
				system_state = STATE_SCREENSAVER;
				graphx_fill_pattern(0x00);
			}

			break;
		}

		lcd_drawbuffer(graphx_buffer());
	}
}
