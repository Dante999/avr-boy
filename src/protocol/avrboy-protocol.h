/**
 * Copyright (C) 2020 dante999
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
#ifndef AVRBOY_PROTOCOL_H
#define AVRBOY_PROTOCOL_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_DATA_LENGTH 16

typedef void (*protocol_transmit)(char byte);
typedef void (*protocol_receive)(void);

struct protocol_package {
	uint8_t cmd;
	uint8_t length;
	char    data[MAX_DATA_LENGTH];
};

void protocol_init(protocol_transmit callback);
void protocol_send(uint8_t cmd, uint8_t length, const char *data);
bool protocol_receive_finished(void);

#endif /* AVRBOY_PROTOCOL_H */
