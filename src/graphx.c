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

#include <stdio.h>
#include <string.h>

#include "graphx.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORIENTATION 0

static uint16_t calculate_index(struct graphxdata *gd, uint8_t x, uint8_t y)
{
#if (ORIENTATION == 0)
	return x + ((y / 8) * graphx_width(gd));
#else
	return y + ((x / 8) * graphx_width(gd));
#endif
}

struct graphxdata *graphx_new(uint8_t width, uint8_t height)
{
	struct graphxdata *gd;

	gd = (struct graphxdata *)malloc(sizeof(struct graphxdata));

	gd->width  = width;
	gd->height = height;

	uint16_t size = graphx_size(gd);

	gd->buffer = (uint8_t *)malloc(size * sizeof(uint8_t));

	memset(gd->buffer, 0x00, size * sizeof(*(gd->buffer)));

	return gd;
}

void graphx_read_from(struct graphxdata *gd, const uint8_t *data)
{
	if (data != NULL) {
		memcpy(gd->buffer, data, graphx_size(gd));
	}
}

void graphx_write_to(struct graphxdata *gd, uint8_t *data)
{
	if (data != NULL) {
		memcpy(data, gd->buffer, graphx_size(gd));
	}
}

uint16_t graphx_size(struct graphxdata *gd)
{
	return (gd->width * (gd->height / 8));
}

uint8_t graphx_width(struct graphxdata *gd)
{
	return gd->width;
}

uint8_t graphx_height(struct graphxdata *gd)
{
	return gd->height;
}

void graphx_destroy(struct graphxdata *gd)
{
	if (gd != NULL && gd->buffer != NULL)
		free(gd->buffer);

	if (gd != NULL) {
		free(gd);
	}
}

void graphx_draw_pixel(struct graphxdata *gd, uint8_t x, uint8_t y,
		       uint8_t color)
{
#if ORIENTATION == 0
	uint8_t y_bit = y % 8;
#else
	uint8_t y_bit = x % 8;
#endif

	uint16_t index = calculate_index(gd, x, y);

	if (color)
		gd->buffer[index] |= (1 << y_bit);
	else
		gd->buffer[index] &= ~(1 << y_bit);
}

uint8_t graphx_get_pixel(struct graphxdata *gd, uint8_t x, uint8_t y)
{
	uint8_t  y_bit = y % 8;
	uint16_t index = calculate_index(gd, x, y);

	if (gd->buffer[index] & (1 << y_bit))
		return 1;
	else
		return 0;
}

void graphx_fill_pattern(struct graphxdata *gd, char pattern)
{
	memset(gd->buffer, pattern, graphx_size(gd) - 1);
}
