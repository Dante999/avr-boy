#include "cartridge.h"

#include <stdint.h>
#include <stdio.h>

#include "protocol.h"

#define LOG_COMMUNICATION

#ifdef LOG_COMMUICATION
#	include "../logger.h"
#endif

static struct protocol_package m_received;

void cartridge_sync_with_handheld(void)
{
	protocol_sync();
}

uint8_t cartridge_ping(void)
{
	protocol_send_package(PRTCL_CMD_PING, 0, 0);
	protocol_waitfor_package(&m_received);

	if (m_received.cmd == PRTCL_CMD_ACK)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_check_version(uint8_t *handheld_version)
{
	char data[1] = {(char)PROTOCOL_VERSION};

	protocol_send_package(PRTCL_CMD_CHECK_VERSION, 1, data);
	protocol_waitfor_package(&m_received);

	*handheld_version = m_received.data[0];

	if (PROTOCOL_VERSION == handheld_version)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_NOK;
}