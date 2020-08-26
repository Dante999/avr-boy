#include "lcd.h"

#include "driver/ks0108.h"
#include "driver/ssd1306.h"
#include "graphx.h"

static void lcd_draw_byte(uint8_t x, uint8_t y, uint8_t byte)
{
	for (uint8_t j = 0; j < 8; j++) {

		uint8_t color =
		    (byte & (1 << j)) ? GRAPHX_PIXEL_ON : GRAPHX_PIXEL_OFF;

		lcd_draw_pixel(x, y + j, color);
	}
}

void lcd_init(void)
{
	ks0108_init();
}

void lcd_draw_pixel(uint8_t x, uint8_t y, uint8_t color)
{
	ks0108_set_pixel(x, y, color);
}

void lcd_scroll(uint8_t line)
{
	ks0108_scroll(line);
}

void lcd_drawbuffer(uint8_t *buffer)
{
	ks0108_drawbuffer(buffer);
}

void lcd_drawbyte(uint8_t page, uint8_t addr, uint8_t byte)
{
	ks0108_draw_byte(page, addr, 1, &byte);
}

void lcd_draw_sprite(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                     const uint8_t *data)
{
	for (uint8_t row = 0; row < (h / 8); row++) {

		for (uint8_t col = 0; col < w; col++) {

			uint16_t offset = row * w;

			uint8_t d_new = data[offset + col];
			uint8_t x_new = x + col;
			uint8_t y_new = y + (row * 8);

			lcd_draw_byte(x_new, y_new, d_new);
		}
	}
}

void lcd_draw_sprite8x8(uint8_t x, uint8_t y, const uint8_t *data)
{
	lcd_draw_sprite(x, y, 8, 8, data);
}