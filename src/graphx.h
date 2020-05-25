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
#ifndef GRAPHX_H
#define GRAPHX_H

#include <stdint.h> // uint8_t

#define PIXEL_ON  1
#define PIXEL_OFF 0

struct graphxdata {
	uint8_t *buffer;
	uint8_t  width;
	uint8_t  height;
};

struct font {
	uint8_t width;
	uint8_t height;
	uint8_t data[];
};

struct graphxdata *graphx_new(uint8_t width, uint8_t height);

void graphx_destroy(struct graphxdata *gd);

void graphx_draw_pixel(struct graphxdata *gd, uint8_t x, uint8_t y,
		       uint8_t color);
void graphx_draw_tile(struct graphxdata *gd, uint8_t x, uint8_t y,
		      uint8_t *tile, uint8_t w, uint8_t h);

void graphx_putc(struct graphxdata *gd, struct font *f, uint8_t x, uint8_t y,
		 const char c);

void graphx_puts(struct graphxdata *gd, struct font *f, uint8_t x, uint8_t y,
		 const char *s);

void graphx_draw_vline(struct graphxdata *gd, uint8_t x, uint8_t y_start,
		       uint8_t y_end, uint8_t color);

void graphx_draw_hline(struct graphxdata *gd, uint8_t x_start, uint8_t x_end,
		       uint8_t y, uint8_t color);

void graphx_print(struct graphxdata *gd);
void graphx_read_from(struct graphxdata *gd, const uint8_t *data);
void graphx_write_to(struct graphxdata *gd, uint8_t *data);
void graphx_fill_pattern(struct graphxdata *gd, char pattern);

uint8_t  graphx_get_pixel(struct graphxdata *gd, uint8_t x, uint8_t y);
uint16_t graphx_size(struct graphxdata *gd);
uint8_t  graphx_width(struct graphxdata *gd);
uint8_t  graphx_height(struct graphxdata *gd);

#endif // GRAPHX_H