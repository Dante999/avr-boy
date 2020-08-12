#include "cartridge.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "protocol.h"

#define LOG_COMMUNICATION 1

#if LOG_COMMUNICATION
#	include "../util/logger.h"
#endif

static struct protocol_package m_received;

static cartridge_cb_is_handheld_ready m_callback_is_cartridge_ready = NULL;

static void wait_until_handheld_ready(void)
{

	if (m_callback_is_cartridge_ready != NULL) {
		while (!m_callback_is_cartridge_ready()) {
			// waiting....
		}
	}
}

static void send_to_handheld(uint8_t cmd, uint8_t length, const char *data)
{
	wait_until_handheld_ready();
	protocol_send_package(cmd, length, data);
	protocol_reset();
}

static void waitfor_handheld_response(struct protocol_package *package)
{
	wait_until_handheld_ready();
	protocol_waitfor_package(package);
}

static uint8_t command_equals(uint8_t expected, uint8_t actual)
{
	if (expected == actual) {
		return CRTRDG_STATUS_OK;
	}
	else {
#if LOG_COMMUNICATION
		char msg[50];
		snprintf(msg, 50, "expected response cmd %d but got %d",
		         expected, actual);
		LOG_ERROR(msg);
#endif
		return CRTRDG_STATUS_WRONG_COMMAND;
	}
}

void cartridge_sync_with_handheld(void)
{
	wait_until_handheld_ready();

	protocol_sync();
}

uint8_t cartridge_ping(void)
{

	send_to_handheld(PRTCL_CMD_PING, 0, NULL);
	waitfor_handheld_response(&m_received);

	if (m_received.cmd == PRTCL_CMD_PONG)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_clear_screen(void)
{
	send_to_handheld(PRTCL_CMD_CLEAR_SCREEN, 0, NULL);
	waitfor_handheld_response(&m_received);

	if (m_received.cmd == PRTCL_CMD_ACK)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_check_version(uint8_t *handheld_version)
{

	char data[1] = {(char)PROTOCOL_VERSION};

	send_to_handheld(PRTCL_CMD_CHECK_VERSION, 1, data);
	waitfor_handheld_response(&m_received);

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

	send_to_handheld(PRTCL_CMD_DRAW_TEXT, sizeof(tmp), (char *)&tmp);
	waitfor_handheld_response(&m_received);

	if (m_received.cmd == PRTCL_CMD_ACK)
		return CRTRDG_STATUS_OK;
	else
		return CRTRDG_STATUS_WRONG_COMMAND;
}

uint8_t cartridge_draw_pixel(uint8_t x, uint8_t y, uint8_t color)
{
	struct pixel tmp;
	tmp.x     = x;
	tmp.y     = y;
	tmp.color = color;

	send_to_handheld(PRTCL_CMD_DRAW_PIXEL, sizeof(struct pixel),
	                 (char *)&tmp);
	waitfor_handheld_response(&m_received);

	return command_equals(PRTCL_CMD_ACK, m_received.cmd);
}

uint8_t cartridge_get_buttons(struct button_stat *btn)
{
	send_to_handheld(PRTCL_CMD_GET_BUTTONS, 0, NULL);
	waitfor_handheld_response(&m_received);

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

void cartridge_set_cb_is_handheld_ready(cartridge_cb_is_handheld_ready cb)
{
	m_callback_is_cartridge_ready = cb;
}

uint8_t cartridge_sprite(const c_sprite_t *sprite)
{
	send_to_handheld(PRTCL_CMD_SPRITE, sizeof(c_sprite_t),
	                 (const char *)sprite);
	waitfor_handheld_response(&m_received);

	return command_equals(PRTCL_CMD_ACK, m_received.cmd);
}

uint8_t cartridge_display_buffer()
{
	send_to_handheld(PRTCL_CMD_DISPLAY_BUFFER, 0, NULL);
	waitfor_handheld_response(&m_received);

	return command_equals(PRTCL_CMD_ACK, m_received.cmd);
}

uint8_t cartridge_display_sprites()
{
	send_to_handheld(PRTCL_CMD_DISPLAY_SPRITES, 0, NULL);
	waitfor_handheld_response(&m_received);

	return command_equals(PRTCL_CMD_ACK, m_received.cmd);
}