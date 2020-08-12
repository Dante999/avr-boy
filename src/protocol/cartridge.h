/**
 * Copyright (C) 2020 Matthias Escher
 *
 * This file is part of avr-boy.
 *
 * avr-boy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * avr-boy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with avr-boy.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>

#include "core.h"
#include "protocol.h"

#define CRTRDG_STATUS_OK            0
#define CRTRDG_STATUS_NOK           1
#define CRTRDG_STATUS_WRONG_COMMAND 2
#define CRTRDG_STATUS_WRONG_DATA    3

typedef bool (*cartridge_cb_is_handheld_ready)(void);

void cartridge_sync_with_handheld(void);
void cartridge_init(protocol_callback_transmit cb_transmit,
                    protocol_callback_receive  cb_receive);

uint8_t cartridge_ping(void);
uint8_t cartridge_check_version(uint8_t *handheld_version);
uint8_t cartridge_draw_text(uint8_t x, uint8_t y, const char *text);
uint8_t cartridge_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
uint8_t cartridge_get_buttons(c_buttonstat_t *btn);
uint8_t cartridge_clear_screen();
uint8_t cartridge_display_buffer();
uint8_t cartridge_display_sprites();
uint8_t cartridge_sprite(const c_sprite_t *sprite);

void cartridge_set_cb_is_handheld_ready(cartridge_cb_is_handheld_ready cb);
#endif /* CARTRIDGE_H */
