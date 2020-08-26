/**
 * Copyright (C) 2020 Matthias Escher
 *
 * This file is part of avr-boy.
 *
 * avr-boy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * avr-boy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with avr-boy.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "graphx.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset

#ifdef __AVR_DEVICE_NAME__
#	define IS_AVR_DEVICE
#endif

#ifdef IS_AVR_DEVICE
#	include <avr/pgmspace.h>
#endif

static struct graphxdata {
	uint8_t width;
	uint8_t height;
	uint8_t buffer[GRAPHX_SIZE];
} g_graphxdata;

static uint16_t calculate_index(uint8_t x, uint8_t y)
{
	return x + ((y / 8) * graphx_width());
}

/** ****************************************************************************
 * @brief initializes the graphx module
 *
 * Sets the graphx width and height like defined in #GRAPHX_WIDTH and
 * #GRAPHX_HEIGHT. Also clears the whole buffer which means that a blank screen
 * would normally be displayed
 *
 **************************************************************************** */
void graphx_init(void)
{
	g_graphxdata.width  = GRAPHX_WIDTH;
	g_graphxdata.height = GRAPHX_HEIGHT;
	graphx_fill_pattern(0x00);
}

void graphx_read_from(const uint8_t *data)
{
	if (data != NULL) {
		memcpy(g_graphxdata.buffer, data, graphx_size());
	}
}

void graphx_write_to(uint8_t *data)
{
	if (data != NULL) {
		memcpy(data, g_graphxdata.buffer, graphx_size());
	}
}

uint16_t graphx_size(void)
{
	return (uint16_t)GRAPHX_SIZE;
}

uint8_t graphx_width(void)
{
	return g_graphxdata.width;
}

uint8_t graphx_height(void)
{
	return g_graphxdata.height;
}

void graphx_draw_pixel(uint8_t x, uint8_t y, uint8_t color)
{

	uint8_t y_bit = y % 8;

	uint16_t index = calculate_index(x, y);

	if (color == GRAPHX_PIXEL_ON)
		g_graphxdata.buffer[index] |= (1 << y_bit);
	else if (color == GRAPHX_PIXEL_TOGGLE)
		g_graphxdata.buffer[index] ^= (1 << y_bit);
	else
		g_graphxdata.buffer[index] &= ~(1 << y_bit);
}

static void graphx_draw_byte(uint8_t x, uint8_t y, uint8_t byte)
{
	for (uint8_t j = 0; j < 8; j++) {

		uint8_t color =
		    (byte & (1 << j)) ? GRAPHX_PIXEL_ON : GRAPHX_PIXEL_OFF;

		graphx_draw_pixel(x, y + j, color);
	}
}

static uint8_t graphx_get_byte(uint8_t x, uint8_t y)
{
	uint8_t result = 0;

	for (uint8_t j = 0; j < 8; j++) {
		result |= graphx_get_pixel(x, y + j) ? (1 << j) : 0;
	}

	return result;
}

void graphx_draw_tile_P(uint8_t x, uint8_t y, const uint8_t *tile, uint8_t w,
                        uint8_t h)
{
	for (uint8_t row = 0; row < (h / 8); row++) {

		for (uint8_t col = 0; col < w; col++) {

			uint16_t offset = row * w;

#ifdef IS_AVR_DEVICE
			uint8_t data = pgm_read_byte(&(tile[offset + col]));
#else
			uint8_t data = tile[offset + col];
#endif
			uint8_t x_new = x + col;
			uint8_t y_new = y + (row * 8);

			graphx_draw_byte(x_new, y_new, data);
		}
	}
}

void graphx_draw_tile(uint8_t x, uint8_t y, const uint8_t *tile, uint8_t w,
                      uint8_t h)
{

	for (uint8_t row = 0; row < (h / 8); row++) {

		for (uint8_t col = 0; col < w; col++) {

			uint16_t offset = row * w;

			uint8_t data  = tile[offset + col];
			uint8_t x_new = x + col;
			uint8_t y_new = y + (row * 8);

			graphx_draw_byte(x_new, y_new, data);
		}
	}
}

void graphx_get_tile(uint8_t x, uint8_t y, uint8_t *target, uint8_t w,
                     uint8_t h)
{

	for (uint8_t row = 0; row < (h / 8); row++) {

		for (uint8_t col = 0; col < w; col++) {

			uint16_t offset = row * w;

			uint8_t x_new = x + col;
			uint8_t y_new = y + (row * 8);

			target[offset + col] = graphx_get_byte(x_new, y_new);
		}
	}
}

void graphx_draw_hline(uint8_t x0, uint8_t x1, uint8_t y, uint8_t color)
{
	uint8_t delta = x1 - x0;

	for (uint8_t i = 0; i <= delta; i++) {
		graphx_draw_pixel(x0 + i, y, color);
	}
}

void graphx_draw_vline(uint8_t x, uint8_t y0, uint8_t y1, uint8_t color)
{
	uint8_t delta = y1 - y0;

	for (uint8_t i = 0; i <= delta; i++) {
		graphx_draw_pixel(x, y0 + i, color);
	}
}

uint8_t graphx_get_pixel(uint8_t x, uint8_t y)
{
	uint8_t  y_bit = y % 8;
	uint16_t index = calculate_index(x, y);

	if (g_graphxdata.buffer[index] & (1 << y_bit))
		return 1;
	else
		return 0;
}

void graphx_putc(const struct font *f, uint8_t x, uint8_t y, const char c)
{
	uint8_t font_width  = font_pgm_width(f);
	uint8_t font_height = font_pgm_height(f);

	uint8_t  char_index  = (uint8_t)c - 0x20;
	uint16_t start_index = char_index * font_width;

	for (uint8_t row = 0; row < (font_height / 8); row++) {

		uint16_t row_offset = row * font_width;

		for (uint8_t col = 0; col < font_width; col++) {

			uint16_t i_new = start_index + row_offset + col;
			uint8_t  x_new = x + col;
			uint8_t  y_new = y + (row * 8);

			graphx_draw_byte(x_new, y_new, font_pgm_byte(f, i_new));
		}
	}
}

void graphx_putc_P(const uint8_t *f, uint8_t x, uint8_t y, const char c)
{
	uint8_t font_width  = font_width_P(f);
	uint8_t font_height = font_height_P(f);

	uint8_t  char_index  = (uint8_t)c - 0x20;
	uint16_t start_index = char_index * font_width;

	for (uint8_t row = 0; row < (font_height / 8); row++) {

		uint16_t row_offset = row * font_width;

		for (uint8_t col = 0; col < font_width; col++) {

			uint16_t i_new = start_index + row_offset + col;
			uint8_t  x_new = x + col;
			uint8_t  y_new = y + (row * 8);

			graphx_draw_byte(x_new, y_new, font_byte_P(f, i_new));
		}
	}
}

void graphx_puts(const struct font *f, uint8_t x, uint8_t y, const char *s)
{
	uint8_t font_width = font_pgm_width(f);

	for (uint8_t i = 0; i < strlen(s); i++) {
		graphx_putc(f, x + (i * (font_width + 1)), y, s[i]);
	}
}

void graphx_puts_P(const uint8_t *f, uint8_t x, uint8_t y, const char *s)
{
	uint8_t font_width = font_width_P(f);

	for (uint8_t i = 0; i < strlen(s); i++) {
		graphx_putc_P(f, x + (i * (font_width + 1)), y, s[i]);
	}
}

void graphx_fill_pattern(uint8_t pattern)
{
	memset(g_graphxdata.buffer, pattern, graphx_size());
}

uint8_t *graphx_buffer(void)
{
	return g_graphxdata.buffer;
}

void graphx_clear(void)
{
	graphx_fill_pattern(0x00);
}

void graphx_draw_sprite(sprite_t *sprite)
{
	uint8_t tmp[SPRITE_MAX_DATA];

	graphx_get_tile(sprite->x, sprite->y, tmp, 8, 8);

	memcpy(sprite->bgdata, tmp, SPRITE_MAX_DATA);

	graphx_draw_tile(sprite->x, sprite->y, sprite->fgdata, 8, 8);
}

void graphx_clear_sprite(const sprite_t *sprite)
{
	graphx_draw_tile(sprite->x, sprite->y, sprite->bgdata, 8, 8);
}
