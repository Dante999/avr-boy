#include "handheld.h"

#include <stdio.h>

#include "../util/logger.h"
#include "handheld_actions.h"

static void answer_draw_text(struct draw_text *dt)
{
	uint8_t response = action_cmd_received_draw_text(dt);
	protocol_send_package(response, 0, NULL);
}

static void answer_ping(void)
{
	uint8_t response = action_cmd_received_ping();
	protocol_send_package(response, 0, NULL);
}

static void answer_version(uint8_t cartridge_version)
{
	uint8_t response = action_cmd_received_version(cartridge_version);

	char data = {(char)PROTOCOL_VERSION};

	protocol_send_package(response, 1, &data);
}

static void answer_get_buttons(void)
{
	struct button_stat btn;

	uint8_t response = action_cmd_received_get_buttons(&btn);

	protocol_send_package(response, sizeof(btn), (const char *)&btn);
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

		char msg[50];

		sprintf(msg, "l=%d|x=%d|y=%d|msg=%s", received->length,
		        (uint8_t)received->data[0], (uint8_t)received->data[1],
		        (char *)&received->data[2]);

		LOG_DEBUG(msg);

		answer_draw_text((struct draw_text *)&received->data[0]);

		break;

	case PRTCL_CMD_GET_BUTTONS:
		LOG_DEBUG("-> get buttons");
		answer_get_buttons();
		break;

	default:
		LOG_WARNING("-> unkown command!");
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
	protocol_waitfor_package(&received);

	char buffer[10];

	sprintf(buffer, "c=%d", received.cmd);
	LOG_DEBUG(buffer);

	execute_command(&received);
}