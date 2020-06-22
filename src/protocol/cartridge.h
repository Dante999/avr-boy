
#include <stdint.h>

#include "protocol.h"

#define CRTRDG_STATUS_OK            0
#define CRTRDG_STATUS_WRONG_COMMAND 1
#define CRTRDG_STATUS_WRONG_DATA    2

uint8_t cartridge_ping(void);
// uint8_t cartridge_check_version(uint8_t *handheld_version);

// uint8_t cartridge_get_buttons(struct button *btn);
// uint8_t cartridge_lcd_draw_pixel(uint8_t x, uint8_t y, uint8_t color);

// uint8_t cartridge_lcd_draw_hline(uint8_t x0, uint8_t x1, uint8_t y,
//                                  uint8_t color);

// uint8_t cartridge_lcd_draw_vline(uint8_t x, uint8_t y0, uint8_t y1,
//                                  uint8_t color);
