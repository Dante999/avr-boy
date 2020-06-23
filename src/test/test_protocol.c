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
#include "unity.h"

#include <string.h>

#include "../protocol/protocol.h"

#define BUFFER_SIZE 255

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

static void test_protocol_receiver_callback(void)
{
	reset_all();

	m_receive_buffer[0] = PRTCL_START_BYTE;
	m_receive_buffer[1] = PRTCL_CMD_CHECK_VERSION;
	m_receive_buffer[2] = 1;
	m_receive_buffer[3] = 2;

	TEST_ASSERT_EQUAL(m_receive_index, 0);

	struct protocol_package received;
	memset(&received, 0x00, sizeof(received));

	protocol_waitfor_package(&received);

	TEST_ASSERT_EQUAL(m_receive_index, 4);

	TEST_ASSERT_EQUAL(received.cmd, PRTCL_CMD_CHECK_VERSION);
	TEST_ASSERT_EQUAL(received.length, 1);
	TEST_ASSERT_EQUAL(received.data[0], 2);
}

static void test_protocol_transmitter_callback(void)
{
	reset_all();

	char data[4] = {1, 2, 3, 4};
	protocol_send_package(data[0], data[1], &data[2]);

	TEST_ASSERT_EQUAL(m_transmit_index, 5);
	TEST_ASSERT_EQUAL(m_transmit_buffer[0], PRTCL_START_BYTE);
	TEST_ASSERT_EQUAL(m_transmit_buffer[1], data[0]);
	TEST_ASSERT_EQUAL(m_transmit_buffer[2], data[1]);
	TEST_ASSERT_EQUAL(m_transmit_buffer[3], data[2]);
	TEST_ASSERT_EQUAL(m_transmit_buffer[4], data[3]);
}

static void test_protocol_receiver_parse_byte(void)
{

	reset_all();

	uint8_t sync    = PRTCL_START_BYTE;
	uint8_t cmd     = PRTCL_CMD_CHECK_VERSION;
	uint8_t length  = 2;
	char    data[2] = {1, 1};

	// should initially set to false
	TEST_ASSERT_EQUAL(protocol_receive_complete(), false);

	protocol_parse_received(sync);
	protocol_parse_received(cmd);
	protocol_parse_received(length);
	protocol_parse_received(data[0]);
	protocol_parse_received(data[1]);

	TEST_ASSERT_EQUAL(protocol_receive_complete(), true);

	// check received data
	struct protocol_package received;
	protocol_copy_received(&received);

	TEST_ASSERT_EQUAL(cmd, received.cmd);
	TEST_ASSERT_EQUAL(length, received.length);
	TEST_ASSERT_EQUAL(data[0], received.data[0]);
	TEST_ASSERT_EQUAL(data[1], received.data[1]);
}

void test_protocol_min_data_length(void)
{
	reset_all();

	uint8_t sync   = PRTCL_START_BYTE;
	uint8_t cmd    = PRTCL_CMD_PING;
	uint8_t length = 0;

	m_receive_buffer[0] = sync;
	m_receive_buffer[1] = cmd;
	m_receive_buffer[2] = length;

	// check received data
	struct protocol_package received;
	protocol_waitfor_package(&received);

	TEST_ASSERT_EQUAL(3, m_receive_index);

	// double check
	m_receive_index     = 0;
	m_receive_buffer[2] = 2; // new length
	m_receive_buffer[3] = 3; // data[0]
	m_receive_buffer[4] = 4; // data[1]

	protocol_waitfor_package(&received);

	TEST_ASSERT_EQUAL(5, m_receive_index);
	TEST_ASSERT_EQUAL(2, received.length);
	TEST_ASSERT_EQUAL(3, received.data[0]);
	TEST_ASSERT_EQUAL(4, received.data[1]);
}

void test_protocol_max_data_length(void)
{
	reset_all();

	uint8_t sync   = PRTCL_START_BYTE;
	uint8_t cmd    = PRTCL_CMD_PING;
	uint8_t length = PROTOCOL_MAX_LENGTH + 1;

	m_receive_buffer[0] = sync;
	m_receive_buffer[1] = cmd;
	m_receive_buffer[2] = length;

	// check received data
	struct protocol_package received;
	protocol_waitfor_package(&received);

	TEST_ASSERT_EQUAL(PROTOCOL_MAX_LENGTH, received.length);
}

void test_protocol_reset_by_multible_start_bytes(void)
{
	reset_all();

	m_receive_buffer[0] = 3;
	m_receive_buffer[1] = 3;
	m_receive_buffer[2] = 3;
	m_receive_buffer[3] = PRTCL_START_BYTE;
	m_receive_buffer[4] = PRTCL_START_BYTE;
	m_receive_buffer[5] = PRTCL_START_BYTE;
	m_receive_buffer[6] = PRTCL_START_BYTE;
	m_receive_buffer[7] = PRTCL_CMD_PING;
	m_receive_buffer[8] = 0;

	// check received data
	struct protocol_package received;
	protocol_waitfor_package(&received);

	TEST_ASSERT_EQUAL(PRTCL_CMD_PING, received.cmd);
	TEST_ASSERT_EQUAL(0, received.length);
}

void test_protocol_sync(void)
{
	reset_all();

	memset(m_transmit_buffer, 0xFF, BUFFER_SIZE);

	protocol_sync();

	for (uint8_t i = 0; i <= PROTOCOL_MAX_LENGTH; i++) {
		TEST_ASSERT_EQUAL(PRTCL_START_BYTE, m_transmit_buffer[i]);
	}

	TEST_ASSERT_EQUAL(0xFF, m_transmit_buffer[PROTOCOL_MAX_LENGTH + 1]);
}

void test_protocol_run(void)
{
	protocol_init(cb_transmit_byte, cb_receive_byte);

	RUN_TEST(test_protocol_receiver_parse_byte);
	RUN_TEST(test_protocol_receiver_callback);
	RUN_TEST(test_protocol_transmitter_callback);
	RUN_TEST(test_protocol_min_data_length);
	RUN_TEST(test_protocol_max_data_length);
	RUN_TEST(test_protocol_reset_by_multible_start_bytes);
	RUN_TEST(test_protocol_sync);
}