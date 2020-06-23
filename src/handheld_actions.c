#include "protocol/handheld_actions.h"
#include "protocol/protocol.h"

uint8_t action_cmd_received_ping(void)
{
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_version(uint8_t cartridge_version)
{
	return (cartridge_version == PROTOCOL_VERSION) ? PRTCL_CMD_ACK
	                                               : PRTCL_CMD_NACK;
}
