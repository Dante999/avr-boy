/*******************************************************************************
 *
 * 8boy emulator - an emulation software for the 8boy hardware
 * Copyright (C) 2019 Matthias Escher
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
#include "graphx.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset

static struct graphxdata {
	uint8_t width;
	uint8_t height;
	uint8_t buffer[GRAPHX_SIZE];
} g_graphxdata;

static uint16_t calculate_index(uint8_t x, uint8_t y)
{
	return x + ((y / 8) * graphx_width());
}

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

	if (color)
		g_graphxdata.buffer[index] |= (1 << y_bit);
	else
		g_graphxdata.buffer[index] &= ~(1 << y_bit);
}

void graphx_draw_byte(uint8_t x, uint8_t y, uint8_t byte)
{
	for (uint8_t j = 0; j < 8; j++) {

		uint8_t color = (byte & (1 << j)) ? PIXEL_ON : PIXEL_OFF;

		graphx_draw_pixel(x, y + j, color);
	}
}

void graphx_draw_tile(uint8_t x, uint8_t y, const uint8_t *tile,
		      uint8_t tile_width, uint8_t tile_height)
{

	for (uint8_t row = 0; row < (tile_height / 8); row++) {

		for (uint8_t col = 0; col < tile_width; col++) {

			uint16_t offset = row * tile_width;

			uint8_t data  = tile[offset + col];
			uint8_t x_new = x + col;
			uint8_t y_new = y + (row * 8);

			graphx_draw_byte(x_new, y_new, data);
		}
	}
}

void graphx_draw_hline(uint8_t x_start, uint8_t x_end, uint8_t y, uint8_t color)
{
	uint8_t delta = x_end - x_start;

	for (uint8_t i = 0; i <= delta; i++) {
		graphx_draw_pixel(x_start + i, y, color);
	}
}

void graphx_draw_vline(uint8_t x, uint8_t y_start, uint8_t y_end, uint8_t color)
{
	uint8_t delta = y_end - y_start;

	for (uint8_t i = 0; i <= delta; i++) {
		graphx_draw_pixel(x, y_start + i, color);
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

void graphx_putc(struct font *f, uint8_t x, uint8_t y, const char c)
{
	uint8_t  offset = (uint8_t)c - 0x20;
	uint16_t index  = offset * f->width;
	uint8_t *data   = (uint8_t *)(&f->data[index]);

	graphx_draw_tile(x, y, data, f->width, f->height);
}

void graphx_puts(struct font *f, uint8_t x, uint8_t y, const char *s)
{
	for (uint8_t i = 0; i < strlen(s); i++) {
		graphx_putc(f, x + (i * (f->width + 1)), y, s[i]);
	}
}

void graphx_fill_pattern(char pattern)
{
	memset(g_graphxdata.buffer, pattern, graphx_size());
}
