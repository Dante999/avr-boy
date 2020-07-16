#include "mock_transceiver.h"

#include <stdint.h>
#include <string.h> // memset

#include "../protocol/protocol.h"

#define BUFFER_SIZE MOCK_BUFFER_SIZE

static char m_transmit_buffer[BUFFER_SIZE] = {0x00};
static char m_receive_buffer[BUFFER_SIZE]  = {0x00};

static uint8_t m_transmit_index = 0;
static uint8_t m_receive_index  = 0;

static void cb_transmit_byte(char byte)
{
	m_transmit_buffer[m_transmit_index] = byte;
	m_transmit_index++;
}

static char cb_receive_byte(void)
{
	char retval = m_receive_buffer[m_receive_index];
	m_receive_index++;

	return retval;
}

void mock_transceiver_reset(void)
{
	protocol_reset();

	protocol_init(cb_transmit_byte, cb_receive_byte);

	memset(m_transmit_buffer, 0x00, BUFFER_SIZE);
	memset(m_receive_buffer, 0x00, BUFFER_SIZE);

	m_transmit_index = 0;
	m_receive_index  = 0;
}

char *mock_transceiver_receivebuffer(void)
{
	return m_receive_buffer;
}

char *mock_transceiver_transmitbuffer(void)
{
	return m_transmit_buffer;
}

uint8_t mock_transceiver_transmitindex(void)
{
	return m_transmit_index;
}

uint8_t mock_transceiver_receiveindex(void)
{
	return m_receive_index;
}

void mock_transceiver_prepare_response(struct protocol_package *p)
{
	m_receive_buffer[0] = PRTCL_START_BYTE;
	m_receive_buffer[1] = p->cmd;
	m_receive_buffer[2] = p->length;

	memcpy(&m_receive_buffer[3], &p->data[0], p->length);
}