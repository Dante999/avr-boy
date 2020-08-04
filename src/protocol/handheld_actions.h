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

#ifndef CARTRIDGE_ACTIONS_H
#define CARTRIDGE_ACTIONS_H

#include <stdint.h>

#include "core.h"

uint8_t action_cmd_received_draw_pixel(struct pixel *pixel);
uint8_t action_cmd_received_draw_text(struct draw_text *dt);
uint8_t action_cmd_received_get_buttons(struct button_stat *b);
uint8_t action_cmd_received_clear_screen();

#endif /* CARTRIDGE_ACTIONS_H */
