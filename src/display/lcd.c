#include "../driver/ks0108.h"
#include "../driver/ssd1306.h"

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
	ssd1306_draw_buffer(buffer);
}

void lcd_drawbyte(uint8_t page, uint8_t addr, uint8_t byte)
{
	ks0108_draw_byte(page, addr, 1, &byte);
}
