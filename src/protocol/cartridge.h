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

#include "protocol.h"

#define CRTRDG_STATUS_OK            0
#define CRTRDG_STATUS_NOK           1
#define CRTRDG_STATUS_WRONG_COMMAND 2
#define CRTRDG_STATUS_WRONG_DATA    3

void cartridge_sync_with_handheld(void);

uint8_t cartridge_ping(void);
uint8_t cartridge_check_version(uint8_t *handheld_version);
uint8_t cartridge_draw_text(uint8_t x, uint8_t y, const char *text);
#endif /* CARTRIDGE_H */
