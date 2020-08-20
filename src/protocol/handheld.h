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

#ifndef AVRBOY_HANDHELD_H
#define AVRBOY_HANDHELD_H

#include "protocol.h"


typedef void (*handheld_cb_before_communicate)(void);
typedef void (*handheld_cb_after_communicate)(void);


void handheld_wait_for_actions(void);
void handheld_init(protocol_callback_transmit cb_transmit,
                   protocol_callback_receive  cb_receive);

void handheld_set_cb_before_communicate(handheld_cb_before_communicate cb);
void handheld_set_cb_after_communicate(handheld_cb_after_communicate cb);


#endif /* AVRBOY_HANDHELD_H */
