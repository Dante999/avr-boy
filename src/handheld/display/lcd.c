#include "lcd.h"

#include "driver/ks0108.h"
#include "driver/ssd1306.h"
#include "graphx.h"

#define LCD_TYPE_KS0108
//#define LCD_TYPE_SSD1306

void lcd_init(void)
{
#ifdef LCD_TYPE_KS0108
	ks0108_init();
#endif

#ifdef LCD_TYPE_SSD1306
	ssd1306_init();
#endif
}

void lcd_draw_pixel(uint8_t x, uint8_t y, uint8_t color)
{
#ifdef LCD_TYPE_KS0108
	ks0108_set_pixel(x, y, color);
#else
	(void)x;
	(void)y;
	(void)color;
#endif
}

void lcd_scroll(uint8_t line)
{
#ifdef LCD_TYPE_KS0108
	ks0108_scroll(line);
#else
	(void)line;
#endif
}

void lcd_drawbuffer(uint8_t *buffer)
{
#ifdef LCD_TYPE_KS0108
	ks0108_drawbuffer(buffer);
#endif

#ifdef LCD_TYPE_SSD1306
	ssd1306_draw_buffer(buffer);
#endif
}

void lcd_draw_sprite8x8(uint8_t x, uint8_t y, const uint8_t *data)
{
	(void)x;
	(void)y;
	(void)data;
}
