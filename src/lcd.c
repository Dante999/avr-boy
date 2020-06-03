#include "driver/ks0108.h"

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
