#include <stdio.h>

#include "../display/font5x7.h"
#include "../display/graphx.h"
#include "../driver/spislave.h"
#include "../util/logger.h"
#include "protocol.h"

static void answer_ping(void)
{
	protocol_package_send(CMD_RES_PING, 0, 0);
}

static void answer_version(uint8_t cartridge_version)
{
	if (PROTOCOL_VERSION != cartridge_version) {
		char buffer[80];

		sprintf(buffer,
		        "different communication versions detected!"
		        "[handheld=%d|cartridge=%d]",
		        PROTOCOL_VERSION, cartridge_version);

		LOG_ERROR(buffer);

		graphx_clear();
		graphx_puts(&font5x7, 0, 0,
		            "handheld and cartridge version do not match!");

		sprintf(buffer, "handheld  : %d", PROTOCOL_VERSION);
		graphx_puts(&font5x7, 0, 8, buffer);

		sprintf(buffer, "cartridge : %d", cartridge_version);
		graphx_puts(&font5x7, 0, 16, buffer);
	}

	protocol_package_send(CMD_RES_VERSION, 1, PROTOCOL_VERSION);
}

static void execute_command(struct protocol_package *received)
{

	switch (received->cmd) {

	case CMD_REQ_PING:
		LOG_DEBUG("-> ping request");
		answer_ping();
		break;

	case CMD_REQ_VERSION:
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
	protocol_package_receive(&received);

	char buffer[10];

	sprintf(buffer, "c=%d", received.cmd);
	LOG_DEBUG(buffer);

	execute_command(&received);
}