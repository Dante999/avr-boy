#include "protocol/handheld_actions.h"

#include "button.h"
#include "display/font5x7.h"
#include "display/graphx.h"
#include "protocol/core.h"
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

uint8_t action_cmd_received_draw_text(struct draw_text *dt)
{
	graphx_puts(&font5x7, dt->x, dt->y, dt->text);

	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_get_buttons(struct button_stat *b)
{
	button_read(b);

	return PRTCL_CMD_ACK;
}