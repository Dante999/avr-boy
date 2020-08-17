#include "protocol/handheld_actions.h"

#include "button.h"
#include "display/font5x7.h"
#include "display/graphx.h"
#include "display/lcd.h"
#include "display/sprite.h"
#include "protocol/core.h"
#include "protocol/protocol.h"

uint8_t action_cmd_received_draw_text(c_text_t *t)
{
	graphx_puts(&font5x7, t->coord.x, t->coord.y, t->text);
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_get_buttons(c_buttonstat_t *b)
{
	button_read(b);
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_clear_screen()
{
	graphx_clear();
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_draw_pixel(c_pixel_t *p)
{
	graphx_draw_pixel(p->coord.x, p->coord.y, p->color);
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_sprite(c_sprite_t *sprite)
{
	const sprite_t *old_sprite = sprite_get(sprite->index);

	if (old_sprite->x != sprite->coord.x ||
	    old_sprite->y != sprite->coord.y) {
		graphx_clear_sprite(old_sprite);
	}

	sprite_set_coord(sprite->index, sprite->coord.x, sprite->coord.y);
	sprite_set_fgdata(sprite->index, sprite->data);
	sprite_set_show(sprite->index, sprite->show);

	graphx_draw_sprite((sprite_t *)sprite_get(sprite->index));

	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_display_buffer(void)
{
	lcd_drawbuffer(graphx_buffer());
	return PRTCL_CMD_ACK;
}

uint8_t action_cmd_received_display_sprites(void)
{

	for (uint8_t i = 0; i < SPRITE_MAX_INDEX; i++) {

		const sprite_t *tmp_sprite = sprite_get(i);

		if (tmp_sprite->show) {
			lcd_draw_sprite8x8(tmp_sprite->x, tmp_sprite->y,
			                   tmp_sprite->fgdata);
		}
	}

	return PRTCL_CMD_ACK;
}