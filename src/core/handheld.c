#include "handheld.h"

#include <stdio.h>

#include "handheld_actions.h"
#include "util/logger.h"
#include "userport.h"

static handheld_cb_before_communicate m_callback_before_communicate = NULL;
static handheld_cb_after_communicate m_callback_after_communicate = NULL;


static void emit_before_communicate(void)
{
	if (m_callback_before_communicate != NULL)
		m_callback_before_communicate();
}

static void emit_after_communicate(void)
{
	if (m_callback_after_communicate != NULL)
		m_callback_after_communicate();
}


static void receive_from_cartridge(struct protocol_package *package)
{
	emit_before_communicate();
	protocol_waitfor_package(package);
	emit_after_communicate();

	protocol_reset();
}

static void send_to_cartridge(uint8_t cmd, uint8_t length, const char *data)
{
	emit_before_communicate();
	protocol_send_package(cmd, length, data);
	emit_after_communicate();

	protocol_reset();
}

static void answer_clear_screen()
{
	uint8_t response = action_cmd_received_clear_screen();
	send_to_cartridge(response, 0, NULL);
}

static void answer_draw_text(c_text_t *dt)
{
	uint8_t response = action_cmd_received_draw_text(dt);
	send_to_cartridge(response, 0, NULL);
}

static void answer_draw_pixel(c_pixel_t *pixel)
{
	uint8_t response = action_cmd_received_draw_pixel(pixel);
	send_to_cartridge(response, 0, NULL);
}

static void answer_ping(void)
{
	send_to_cartridge(PRTCL_CMD_PONG, 0, 0);
}

static void answer_version(uint8_t cartridge_version)
{
	uint8_t response = (cartridge_version == PROTOCOL_VERSION)
	                       ? PRTCL_CMD_ACK
	                       : PRTCL_CMD_NACK;

	char data = {(char)PROTOCOL_VERSION};

	send_to_cartridge(response, 1, &data);
}

static void answer_get_buttons(void)
{
	c_buttonstat_t btn;

	uint8_t response = action_cmd_received_get_buttons(&btn);

	send_to_cartridge(response, sizeof(btn), (const char *)&btn);
}

static void answer_sprite(c_sprite_t *sprite)
{
	uint8_t response = action_cmd_received_sprite(sprite);
	send_to_cartridge(response, 0, NULL);
}

static void answer_display_buffer(void)
{
	uint8_t response = action_cmd_received_display_buffer();
	send_to_cartridge(response, 0, NULL);
}

static void answer_display_sprites(void)
{
	uint8_t response = action_cmd_received_display_sprites();
	send_to_cartridge(response, 0, NULL);
}

static void execute_command(struct protocol_package *received)
{
	switch (received->cmd) {

	case PRTCL_CMD_PING:
		LOG_DEBUG("-> ping request");
		answer_ping();
		break;

	case PRTCL_CMD_CHECK_VERSION:
		LOG_DEBUG("-> version request");
		answer_version((uint8_t)received->data[0]);
		break;

	case PRTCL_CMD_DRAW_TEXT:
		LOG_DEBUG("-> draw text");
		answer_draw_text((c_text_t *)&received->data[0]);
		break;

	case PRTCL_CMD_DRAW_PIXEL:
		LOG_DEBUG("-> draw pixel");
		answer_draw_pixel((c_pixel_t *)&received->data[0]);
		break;

	case PRTCL_CMD_CLEAR_SCREEN:
		LOG_DEBUG("-> clear screen");
		answer_clear_screen();
		break;

	case PRTCL_CMD_GET_BUTTONS:
		LOG_DEBUG("-> get buttons");
		answer_get_buttons();
		break;

	case PRTCL_CMD_SPRITE:
		LOG_DEBUG("-> sprite");
		answer_sprite((c_sprite_t *)&received->data[0]);
		break;

	case PRTCL_CMD_DISPLAY_BUFFER:
		LOG_DEBUG("-> display buffer");
		answer_display_buffer();
		break;

	case PRTCL_CMD_DISPLAY_SPRITES:
		LOG_DEBUG("-> display sprites");
		answer_display_sprites();
		break;

	default:
		LOG_WARNING("-> unkown command!");
		send_to_cartridge(PRTCL_CMD_NACK, 0, NULL);
		break;
	}
}

void handheld_init(protocol_callback_transmit cb_transmit,
                   protocol_callback_receive  cb_receive)
{
	protocol_init(cb_transmit, cb_receive);
}

void handheld_wait_for_actions(void)
{
	struct protocol_package received;

	LOG_DEBUG("waiting for commands...");

	userport_11(USERPORT_HIGH);
	receive_from_cartridge(&received);
	userport_11(USERPORT_LOW);

	userport_12(USERPORT_HIGH);
	execute_command(&received);
	userport_12(USERPORT_LOW);
}


void handheld_set_cb_before_communicate(handheld_cb_before_communicate cb)
{
	m_callback_before_communicate = cb;
}

void handheld_set_cb_after_communicate(handheld_cb_after_communicate cb)
{
	m_callback_after_communicate = cb;
}
