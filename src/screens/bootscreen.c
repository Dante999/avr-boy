#include "bootscreen.h"

#include <avr/io.h>
#include <util/delay.h>

#include "display/graphx.h"
#include "display/lcd.h"

#define Y_SCROLL              40
#define SCROLL_DELAY_MS       30
#define BOOTSCREEN_VISIBLE_MS 1000

#define X_OFFSET 25
#define Y_OFFSET 10

#define BOOTSCREEN_WIDTH  72
#define BOOTSCREEN_HEIGHT 16

static uint8_t bmp_bootscreen[] = {
    0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x38, 0x0e, 0x0e, 0xf8, 0x80, 0x00,
    0x00, 0x06, 0x7c, 0xc0, 0x00, 0x00, 0xc0, 0x7c, 0x02, 0x00, 0x00, 0xfe,
    0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x42, 0x42, 0x42, 0x42, 0xa4,
    0x18, 0x00, 0x00, 0xf0, 0x0c, 0x02, 0x02, 0x02, 0x02, 0x0c, 0xf0, 0x00,
    0x00, 0x06, 0x18, 0x60, 0x80, 0x60, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x58, 0x5f, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5f, 0x58,
    0x40, 0x40, 0x40, 0x47, 0x58, 0x58, 0x47, 0x40, 0x40, 0x40, 0x40, 0x5f,
    0x40, 0x40, 0x40, 0x43, 0x44, 0x58, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x5f, 0x50, 0x50, 0x50, 0x50, 0x48,
    0x47, 0x40, 0x40, 0x43, 0x4c, 0x50, 0x50, 0x50, 0x50, 0x4c, 0x43, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x5f, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00};

void bootscreen_show(void)
{
	graphx_fill_pattern(0x00);

	graphx_draw_tile(X_OFFSET, Y_OFFSET, bmp_bootscreen, BOOTSCREEN_WIDTH,
	                 BOOTSCREEN_HEIGHT);

	lcd_drawbuffer(graphx_buffer());

	for (uint8_t i = 64; i > Y_SCROLL; i--) {
		lcd_scroll(i);
		_delay_ms(SCROLL_DELAY_MS);
	}

	_delay_ms(BOOTSCREEN_VISIBLE_MS);

	graphx_fill_pattern(0x00);

	lcd_drawbuffer(graphx_buffer());
	lcd_scroll(0);
}
