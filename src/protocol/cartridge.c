#include "cartridge.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "protocol.h"

#define LOG_COMMUNICATION 0

#if LOG_COMMUNICATION
#	include "../util/logger.h"
#endif

static struct protocol_package m_received;

void cartridge_sync_with_handheld(void)
{
	protocol_sync();
}

uint8_t cartridge_ping(void)
{
	protocol_send_package(PRTCL_CMD_PING, 0, NULL);
	protocol_waitfor_package(&m_received);

	if (m_received.cmd == PRTCL_CMD_PONG)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_clear_screen(void)
{
	protocol_send_package(PRTCL_CMD_CLEAR_SCREEN, 0, NULL);
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

	*handheld_version = (uint8_t)m_received.data[0];

	if (PROTOCOL_VERSION == *handheld_version)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_NOK;
}

uint8_t cartridge_draw_text(uint8_t x, uint8_t y, const char *text)
{
	struct draw_text tmp;

	tmp.x = x;
	tmp.y = y;

	size_t maxlen = sizeof(tmp.text);

	strncpy(tmp.text, text, maxlen);
	tmp.text[maxlen - 1] = '\0'; // extra string terminator

	protocol_send_package(PRTCL_CMD_DRAW_TEXT, sizeof(tmp), (char *)&tmp);
	protocol_waitfor_package(&m_received);

	if (m_received.cmd == PRTCL_CMD_ACK)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_get_buttons(struct button_stat *btn)
{
	protocol_send_package(PRTCL_CMD_GET_BUTTONS, 0, NULL);
	protocol_waitfor_package(&m_received);

	if (sizeof(struct button_stat) != m_received.length) {
		return CRTRDG_STATUS_WRONG_DATA;
	}
	else {
		memcpy(btn, m_received.data, m_received.length);
		return CRTRDG_STATUS_OK;
	}
}

void cartridge_init(protocol_callback_transmit cb_transmit,
                    protocol_callback_receive  cb_receive)
{
	protocol_init(cb_transmit, cb_receive);
}