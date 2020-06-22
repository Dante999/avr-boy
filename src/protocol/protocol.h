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

#define PROTOCOL_MAX_LENGTH 16
#define PROTOCOL_VERSION    1

enum commands {
	CMD_SYNC,
	CMD_ACK,
	CMD_NACK,
	CMD_REQ_PING,
	CMD_RES_PING,
	CMD_REQ_VERSION,
	CMD_RES_VERSION,
	CMD_GET_BUTTONS,
};

typedef void (*protocol_callback_transmit)(char byte);
typedef char (*protocol_callback_receive)(void);

struct protocol_package {
	uint8_t cmd;
	uint8_t length;
	char    data[PROTOCOL_MAX_LENGTH];
};

void protocol_init(protocol_callback_transmit cb_transmit,
                   protocol_callback_receive  cb_receive);

void protocol_package_send(uint8_t cmd, uint8_t length, const char *data);
void protocol_package_receive(struct protocol_package *package);
bool protocol_parse_received(char c);
bool protocol_receive_complete(void);
void protocol_copy_received(struct protocol_package *package);
void protocol_reset(void);

#endif /* AVRBOY_PROTOCOL_H */