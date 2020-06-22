#include "cartridge.h"

#include <stdint.h>
#include <stdio.h>

#include "protocol.h"

#define LOG_COMMUNICATION

#ifdef LOG_COMMUICATION
#	include "../logger.h"
#endif

static struct protocol_package m_received;

// static void wait_for_completion(struct protocol_package *received)
// {
// 	while (!protocol_receive_complete) {
// 		// wait...
// 	}

// 	protocol_copy_received(&received);
// }

// static bool expected_cmd(struct protocol_package *received, uint8_t cmd)
// {

// 	if (received->cmd == cmd) {
// 		return true;
// 	}
// 	else {

// #ifdef LOG_COMMUNICATION
// 		char msg[50];
// 		sprintf(msg, "Expected response cmd %d but got %d", cmd,
// 		        received->cmd);

// 		LOG_WARNING(msg);
// #endif
// 		return false;
// 	}
// }

// uint8_t avrboy_request_version(uint8_t own_version)
// {
// 	protocol_send_package(PRTCL_CMD_CHECK_VERSION, own_version, 0);

// 	wait_for_completion(&m_received);
// 	expected_cmd(&m_received, CMD_RES_VERSION);

// 	return m_received.data[0];
// }

// uint8_t avrboy_response_version(uint8_t version)
// {
// 	protocol_send_package(CMD_RES_VERSION, 1, version);
// }

// uint8_t avrboy_request_ping(void)
// {
// 	protocol_send_package(PRTCL_CMD_PING, 0, 0);

// 	wait_for_completion(&m_received);
// 	expected_cmd(&m_received, CMD_RES_PING);

// 	return 1;
// }

// uint8_t avrboy_response_ping(void)
// {
// 	protocol_send_package(PRTCL_CMD_PING, 0, 0);
// }

uint8_t cartridge_ping(void)
{
	protocol_send_package(PRTCL_CMD_PING, 0, 0);
	protocol_waitfor_package(&m_received);

	if (m_received.cmd == PRTCL_CMD_ACK)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

// uint8_t cartridge_check_version(uint8_t *handheld_version)
// {
// 	protocol_send_package(PRTCL_CMD_CHECK_VERSION, 1, COM_VERSION);
// 	protocol_waitfor_package(&m_received);

// 	if (COM_VERSION == m_received.data[0])
// 		return CRTRDG_STATUS_OK;
// 	else
// 		return CRTRDG_STATUS_WRONG_DATA;
// }