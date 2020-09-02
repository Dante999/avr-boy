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

#include "ball.hpp"
#include "core/cartridge.h"
#include "driver/spimaster.hpp"
#include "driver/uart.hpp"
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
	SpriteList::init();

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
	cartridge_draw_text(5, 8, "Hello World!");
	cartridge_draw_text(5, 16, "This is a small");
	cartridge_draw_text(5, 24, "demonstration");
	cartridge_display_buffer();

	const uint8_t x_min = 0;
	const uint8_t x_max = 127 - 8;
	const uint8_t y_min = 0;
	const uint8_t y_max = 64 - 8;

	Ball ball1(SpriteList::SPRITE_BALL1, x_min, x_max, y_min, y_max);
	ball1.set(10, 5);
	ball1.set_startdir(Ball::DIR_UP);

	Ball ball2(SpriteList::SPRITE_BALL2, x_min, x_max, y_min, y_max);
	ball2.set(30, 10);
	ball2.set_startdir(Ball::DIR_DOWN);

	Ball ball3(SpriteList::SPRITE_BALL3, x_min, x_max, y_min, y_max);
	ball3.set(50, 15);
	ball3.set_startdir(Ball::DIR_LEFT);

	Ball ball4(SpriteList::SPRITE_BALL4, x_min, x_max, y_min, y_max);
	ball4.set(70, 20);
	ball4.set_startdir(Ball::DIR_RIGHT);

	Ball ball5(SpriteList::SPRITE_BALL5, x_min, x_max, y_min, y_max);
	ball5.set(90, 25);
	ball5.set_startdir(Ball::DIR_UPLEFT);

	while (1) {

		ball1.bounce();
		ball2.bounce();
		ball3.bounce();
		ball4.bounce();
		ball5.bounce();

		cartridge_sprite(ball1.sprite());
		cartridge_sprite(ball2.sprite());
		cartridge_sprite(ball3.sprite());
		cartridge_sprite(ball4.sprite());
		cartridge_sprite(ball5.sprite());

		cartridge_display_buffer();

	} // end of main-loop

} // end of main()
