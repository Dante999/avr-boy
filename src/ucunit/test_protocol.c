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

#include <string.h>

#include "../protocol/avrboy-protocol.h"
#include "../protocol/commands.h"
#include "uCUnit-v1.0.h"
#include "util.h"

#define BUFFER_SIZE 20

static char m_buffer[BUFFER_SIZE] = {0x00};

static uint8_t m_index = 0;

void transmit(char byte)
{
	m_buffer[m_index] = byte;
	m_index++;
}

static void clear_buffer(void)
{
	m_index = 0;
	memset(m_buffer, 0x00, BUFFER_SIZE);
}

static void test_transmitter(void)
{
	UCUNIT_TestcaseBegin("avrboy-protocol.c : protocol_send");

	char strbuffer[40] = {0x00};
	char data[4]       = {1, 2, 3, 4};
	protocol_send(data[0], data[1], &data[2]);

	CHECK_u8_equals(m_index, 5, "m_index did not match!");
	CHECK_u8_equals(m_buffer[0], CMD_SYNC, "m_buffer[0] == CMD_SYNC");
	CHECK_u8_equals(m_buffer[1], data[0], "m_buffer[1] did not match!");
	CHECK_u8_equals(m_buffer[2], data[1], "m_buffer[2] did not match!");
	CHECK_u8_equals(m_buffer[3], data[2], "m_buffer[3] did not match!");
	CHECK_u8_equals(m_buffer[4], data[3], "m_buffer[4] did not match!");

	UCUNIT_TestcaseEnd();
}

void test_protocol_run(void)
{
	clear_buffer();
	protocol_init(transmit);

	test_transmitter();

	UCUNIT_WriteSummary();
}