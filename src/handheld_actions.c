#include "protocol/handheld_actions.h"

#include "button.h"
#include "display/font5x7.h"
#include "display/graphx.h"
#include "display/lcd.h"
#include "display/sprite.h"
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

uint8_t action_cmd_received_draw_pixel(struct pixel *p)
{
	graphx_draw_pixel(p->x, p->y, p->color);
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_sprite(c_sprite_t *sprite)
{
	sprite_set_coord(sprite->index, sprite->coord.x, sprite->coord.y);
	sprite_set_data(sprite->index, sprite->data);
	sprite_set_show(sprite->index, sprite->show);

	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_display_buffer(void)
{
	lcd_drawbuffer(graphx_buffer());
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_display_sprites(void)
{
	const sprite_t *tmp_sprite = sprite_get(0);

	if (tmp_sprite->show) {
		lcd_draw_sprite8x8(tmp_sprite->x, tmp_sprite->y,
		                   tmp_sprite->data);
	}

	return PRTCL_CMD_ACK;
}