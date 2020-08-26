/*******************************************************************************
 * @file main.c
 *
 * author               : dante999
 *
 * brief                : just a little demonstration of the ssd1306 library
 *
 * description          : this demonstrates how the lcd-library work.
 *
 * supported devices    : all avr-devices, testet with attiny85
 *
 * usage                :
 *
 *
 *******************************************************************************/

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "driver/spimaster.hpp"
#include "driver/uart.hpp"
#include "core/cartridge.h"
#include "spaceship.h"
#include "util/logger.h"

#ifndef F_CPU
#	define F_CPU 16500000UL
#endif

#define DDRX_READY  DDRB
#define PORTX_READY PORTB
#define PINX_READY  PINB
#define BIT_READY   (1 << PB1)

static void loop_until_handheld_ready(void)
{
	while (!(PINX_READY & BIT_READY)) {
		// wait...
	}
}

static void cb_before_communicate(void)
{
	//	spi_enable_slave();
	//	_delay_ms(50);
	loop_until_handheld_ready();
}

static void cb_after_communicate(void)
{
	SPI::disable_slave();
	_delay_ms(2);
	SPI::enable_slave();
}

static void cb_transmit(char c)
{
	SPI::transceive(c);
}
static char cb_receive(void)
{
	return SPI::transceive(PRTCL_CMD_ACK);
}

static void animate_spaceship(Spaceship &ship)
{
	static const uint8_t y_min = 9;
	static const uint8_t y_max = 50;

	static uint8_t y   = 0;
	static uint8_t dir = 0;

	ship.move(y, 30);

	if (dir == 1) {

		if (y < y_max) {
			y++;
		}
		else {
			dir = 0;
			y--;
		}
	}
	else {

		if (y > y_min) {
			y--;
		}
		else {
			dir = 1;
			y++;
		}
	}

	cartridge_sprite(ship.get_sprite(Spaceship::POS_TOPLEFT));
	cartridge_sprite(ship.get_sprite(Spaceship::POS_TOPRIGHT));
	cartridge_sprite(ship.get_sprite(Spaceship::POS_BOTLEFT));
	cartridge_sprite(ship.get_sprite(Spaceship::POS_BOTRIGHT));
}

/*******************************************************************************
 * @brief   the main function
 *
 * @param   none
 *
 * @return  none
 *******************************************************************************/
int main(void)
{
	loop_until_handheld_ready();

	SPI::init_hw();
	Uart::init_hw();

	LOG_INFO("----------------------------------");
	LOG_INFO("|          AVR BOY - CARTRIDGE   |");
	LOG_INFO("----------------------------------");
	LOG_INFO("initialization done!");

	cartridge_init(cb_transmit, cb_receive);
	cartridge_set_cb_before_communicate(cb_before_communicate);
	cartridge_set_cb_after_communicate(cb_after_communicate);

	LOG_INFO("start syncing with handheld");

	cartridge_sync_with_handheld();

	uint8_t j = 0;

	LOG_INFO("pinging handheld...");
	uint8_t status = cartridge_ping();

	while (status != CRTRDG_STATUS_OK) {

		if (j >= 10) {
			LOG_ERROR("->force re-sync");
			cartridge_sync_with_handheld();
			j = 0;
		}

		j++;

		status = cartridge_ping();
	}

	LOG_INFO("pinging successfull...");

	cartridge_clear_screen();
	cartridge_draw_text(5, 5, "Hello World!");
	cartridge_display_buffer();

	Spaceship ship;

	while (1) {

		animate_spaceship(ship);
		cartridge_display_buffer();

	} // end of main-loop

} // end of main()
