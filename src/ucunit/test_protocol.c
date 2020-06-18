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
#include "system.h"
#include "uCUnit-v1.0.h"

#define BUFFER_SIZE 20

static char m_transmit_buffer[BUFFER_SIZE] = {0x00};
static char m_receive_buffer[BUFFER_SIZE]  = {0x00};

static uint8_t m_transmit_index = 0;
static uint8_t m_receive_index  = 0;

void cb_transmit_byte(char byte)
{
	m_transmit_buffer[m_transmit_index] = byte;
	m_transmit_index++;
}

char cb_receive_byte(void)
{
	char retval = m_receive_buffer[m_receive_index];
	m_receive_index++;

	return retval;
}

static void reset_all(void)
{
	protocol_reset();

	memset(m_transmit_buffer, 0x00, BUFFER_SIZE);
	memset(m_receive_buffer, 0x00, BUFFER_SIZE);

	m_transmit_index = 0;
	m_receive_index  = 0;
}

static void test_receiver_callback(void)
{
	UCUNIT_TestcaseBegin("avrboy-protocol.c : receive");
	reset_all();

	m_receive_buffer[0] = CMD_SYNC;
	m_receive_buffer[1] = CMD_REQ_VERSION;
	m_receive_buffer[2] = 1;
	m_receive_buffer[3] = 2;

	UCUNIT_CheckIsEqual(m_receive_index, 0);

	struct protocol_package received;
	memset(&received, 0x00, sizeof(received));

	protocol_package_receive(&received);

	UCUNIT_CheckIsEqual(m_receive_index, 4);

	UCUNIT_CheckIsEqual(received.cmd, CMD_REQ_VERSION);
	UCUNIT_CheckIsEqual(received.length, 1);
	UCUNIT_CheckIsEqual(received.data[0], 2);

	UCUNIT_TestcaseEnd();
}

static void test_transmitter_callback(void)
{
	UCUNIT_TestcaseBegin("avrboy-protocol.c : protocol_package_send");
	reset_all();

	char data[4] = {1, 2, 3, 4};
	protocol_package_send(data[0], data[1], &data[2]);

	UCUNIT_CheckIsEqual(m_transmit_index, 5);
	UCUNIT_CheckIsEqual(m_transmit_buffer[0], CMD_SYNC);
	UCUNIT_CheckIsEqual(m_transmit_buffer[1], data[0]);
	UCUNIT_CheckIsEqual(m_transmit_buffer[2], data[1]);
	UCUNIT_CheckIsEqual(m_transmit_buffer[3], data[2]);
	UCUNIT_CheckIsEqual(m_transmit_buffer[4], data[3]);

	UCUNIT_TestcaseEnd();
}

static void test_receiver_parse_byte(void)
{

	UCUNIT_TestcaseBegin("avrboy-protocol.c : protocol_package_receive");
	reset_all();

	uint8_t sync    = CMD_SYNC;
	uint8_t cmd     = CMD_REQ_VERSION;
	uint8_t length  = 2;
	char    data[2] = {1, 1};

	// should initially set to false
	UCUNIT_CheckIsEqual(protocol_receive_complete(), false);

	protocol_parse_received(sync);
	protocol_parse_received(cmd);
	protocol_parse_received(length);
	protocol_parse_received(data[0]);
	protocol_parse_received(data[1]);

	UCUNIT_CheckIsEqual(protocol_receive_complete(), true);

	// check received data
	struct protocol_package received;
	protocol_copy_received(&received);

	UCUNIT_CheckIsEqual(cmd, received.cmd);
	UCUNIT_CheckIsEqual(length, received.length);
	UCUNIT_CheckIsEqual(data[0], received.data[0]);
	UCUNIT_CheckIsEqual(data[1], received.data[1]);

	UCUNIT_TestcaseEnd();
}

void test_protocol_run(void)
{
	protocol_init(cb_transmit_byte, cb_receive_byte);

	test_receiver_parse_byte();
	test_receiver_callback();
	test_transmitter_callback();

	UCUNIT_WriteSummary();
}