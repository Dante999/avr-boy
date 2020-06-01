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
#include "screensaver.h"

#include "driver/ks0108.h"
#include "graphx.h"

#define TILE_BALL_WIDTH  2
#define TILE_BALL_HEIGHT 8

#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 127
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 63

enum direction {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP_LEFT,
	DIR_UP_RIGHT,
	DIR_DOWN_LEFT,
	DIR_DOWN_RIGHT
};

static const uint8_t tile_ball[]  = {0x81, 0x81};
static const uint8_t tile_empty[] = {0x00, 0x00};

static uint8_t        x              = 0;
static uint8_t        y              = 0;
static enum direction ball_direction = DIR_DOWN_RIGHT;

void screensaver_init(void)
{
	graphx_fill_pattern(0x00);
}

static void move_down()
{
	if (y < SCREEN_Y_MAX) {
		y++;
	}
	else {
		y--;
		ball_direction = DIR_UP;
	}
}

static void move_up()
{
	if (y > SCREEN_Y_MIN) {
		y--;
	}
	else {
		y++;
		ball_direction = DIR_DOWN;
	}
}

static void move_right()
{
	if (x < SCREEN_X_MAX) {
		x++;
	}
	else {
		x--;
		ball_direction = DIR_LEFT;
	}
}

static void move_left()
{
	if (x > SCREEN_X_MIN) {
		x--;
	}
	else {
		x++;
		ball_direction = DIR_RIGHT;
	}
}

static void move_upleft()
{
	if (x > SCREEN_X_MIN) {
		x--;
	}
	else {
		x++;
		ball_direction = DIR_UP_RIGHT;
	}

	if (y > SCREEN_Y_MIN) {
		y--;
	}
	else {
		y++;
		ball_direction = DIR_DOWN_LEFT;
	}
}

static void move_upright()
{
	if (x < SCREEN_X_MAX) {
		x++;
	}
	else {
		x--;
		ball_direction = DIR_UP_LEFT;
	}

	if (y > SCREEN_Y_MIN) {
		y--;
	}
	else {
		y++;
		ball_direction = DIR_DOWN_RIGHT;
	}
}

static void move_downleft()
{
	if (x > SCREEN_X_MIN) {
		x--;
	}
	else {
		x++;
		ball_direction = DIR_DOWN_RIGHT;
	}

	if (y < SCREEN_Y_MAX) {
		y++;
	}
	else {
		y--;
		ball_direction = DIR_UP_LEFT;
	}
}

static void move_downright()
{
	if (x < SCREEN_X_MAX) {
		x++;
	}
	else {
		x--;
		ball_direction = DIR_DOWN_LEFT;
	}

	if (y < SCREEN_Y_MAX) {
		y++;
	}
	else {
		y--;
		ball_direction = DIR_UP_RIGHT;
	}
}

void screensaver_run(uint8_t speed)
{
	static uint8_t i = 0;

	i++;

	if (i < speed) {
		return;
	}
	else {
		i = 0;
	}

	switch (ball_direction) {
	case DIR_UP:
		move_up();
		break;

	case DIR_DOWN:
		move_down();
		break;

	case DIR_LEFT:
		move_left();
		break;

	case DIR_RIGHT:
		move_right();
		break;

	case DIR_UP_LEFT:
		move_upleft();
		break;

	case DIR_UP_RIGHT:
		move_upright();
		break;

	case DIR_DOWN_LEFT:
		move_downleft();
		break;

	case DIR_DOWN_RIGHT:
		move_downright();
		break;
	}

	ks0108_set_pixel(x, y, 1);
	// graphx_draw_pixel(x, y, PIXEL_ON);
}
