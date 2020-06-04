/*******************************************************************************
 * @file ssd1306.h
 *
 * author               : dante999
 *
 * see the source-file for further documentation
 *
 *******************************************************************************/
#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

/*******************************************************************************
 * function prototypes
 *******************************************************************************/
void ssd1306_draw_tile_xy(uint8_t x, uint8_t y, uint8_t *tile);
void ssd1306_init(void);
void ssd1306_fill(uint8_t symbol);
void ssd1306_draw_tile_colpage(uint8_t column, uint8_t page, uint8_t *tile);

void ssd1306_draw_buffer(uint8_t *buffer);
#endif
