#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void lcd_init(void);
void lcd_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void lcd_scroll(uint8_t line);
void lcd_drawbuffer(uint8_t *buffer);

#endif // LCD_H
