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

#include "font.h"

#include <stdint.h> // uint8_t

#define GRAPHX_PIXEL_OFF    0
#define GRAPHX_PIXEL_ON     1
#define GRAPHX_PIXEL_TOGGLE 2

#define GRAPHX_WIDTH  128
#define GRAPHX_HEIGHT 64
#define GRAPHX_SIZE   (GRAPHX_WIDTH * (GRAPHX_HEIGHT / 8))

void graphx_draw_tile_P(uint8_t x, uint8_t y, const uint8_t *tile, uint8_t w,
                        uint8_t h);
void graphx_draw_tile(uint8_t x, uint8_t y, const uint8_t *tile, uint8_t w,
                      uint8_t h);

void graphx_putc(const struct font *f, uint8_t x, uint8_t y, const char c);
void graphx_puts(const struct font *f, uint8_t x, uint8_t y, const char *s);

void graphx_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void graphx_draw_vline(uint8_t x, uint8_t y0, uint8_t y1, uint8_t color);
void graphx_draw_hline(uint8_t x0, uint8_t x1, uint8_t y, uint8_t color);

void graphx_read_from(const uint8_t *data);
void graphx_write_to(uint8_t *data);
void graphx_fill_pattern(uint8_t pattern);
void graphx_clear(void);

uint8_t *graphx_buffer(void);

uint8_t  graphx_get_pixel(uint8_t x, uint8_t y);
uint16_t graphx_size(void);
uint8_t  graphx_width(void);
uint8_t  graphx_height(void);
void     graphx_init(void);

#endif // GRAPHX_H
