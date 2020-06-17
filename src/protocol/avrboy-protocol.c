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
#include "avrboy-protocol.h"

#include "commands.h"

enum state { WAITFOR_SYNC, WAITFOR_CMD, WAITFOR_LENGTH, WAITFOR_DATA };

static enum state              m_state = WAITFOR_SYNC;
static struct protocol_package m_package;

static protocol_transmit callback_transmit;
static protocol_receive  callback_receive;
static volatile bool     is_finished = false;

static void parse_byte(char byte)
{
	static uint8_t i = 0;

	switch (m_state) {
	case WAITFOR_SYNC:

		if (byte == CMD_SYNC) {
			i       = 0;
			m_state = WAITFOR_CMD;
		}

		break;

	case WAITFOR_CMD:
		m_package.cmd = byte;
		m_state       = WAITFOR_LENGTH;
		break;

	case WAITFOR_LENGTH:
		m_package.length = byte;
		m_state          = WAITFOR_DATA;
		break;

	case WAITFOR_DATA:

		if (i < m_package.length) {
			m_package.data[i] = byte;
			i++;
		}

		if (i >= m_package.length || i >= MAX_DATA_LENGTH) {
			m_state = WAITFOR_SYNC;
			i       = 0;
		}

		break;
	}
}

bool protocol_receive_finished(void)
{
	return is_finished;
}

void protocol_send(uint8_t cmd, uint8_t length, const char *data)
{
	callback_transmit(CMD_SYNC);
	callback_transmit(cmd);
	callback_transmit(length);

	for (uint8_t i = 0; i < length; i++) {
		callback_transmit(data[i]);
	}
}

void protocol_init(protocol_transmit callback)
{
	callback_transmit = callback;
}