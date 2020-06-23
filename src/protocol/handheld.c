#include "handheld.h"

#include <stdio.h>

#include "../util/logger.h"
#include "handheld_actions.h"

static void answer_ping(void)
{
	uint8_t response = action_cmd_received_ping();
	protocol_send_package(response, 0, NULL);
}

static void answer_version(uint8_t cartridge_version)
{
	uint8_t response = action_cmd_received_version(cartridge_version);

	char data[1] = {(char)PROTOCOL_VERSION};

	protocol_send_package(response, 1, data);
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
		answer_version(received->data[0]);
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