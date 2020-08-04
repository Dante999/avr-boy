#include "protocol/handheld_actions.h"

#include "button.h"
#include "display/font5x7.h"
#include "display/graphx.h"
#include "protocol/core.h"
#include "protocol/protocol.h"

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

uint8_t action_cmd_received_clear_screen()
{
	graphx_clear();
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_draw_pixel(struct pixel *pixel)
{
	graphx_draw_pixel(pixel->x, pixel->y, pixel->color);
	return PRTCL_CMD_ACK;
}