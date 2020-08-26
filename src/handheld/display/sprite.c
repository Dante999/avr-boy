
#include "sprite.h"
#include <string.h> // memcpy

static sprite_t m_sprites[SPRITE_MAX_INDEX];

void sprite_init(void)
{
	for (uint8_t i = 0; i < SPRITE_MAX_INDEX; i++) {
		sprite_set_show(i, false);
	}
}

void sprite_set_coord(uint8_t index, uint8_t x, uint8_t y)
{
	m_sprites[index].x = x;
	m_sprites[index].y = y;
}

void sprite_set_fgdata(uint8_t index, const uint8_t *data)
{
	memcpy(m_sprites[index].fgdata, data, SPRITE_MAX_DATA);
}

void sprite_set_bgdata(uint8_t index, const uint8_t *data)
{
	memcpy(m_sprites[index].bgdata, data, SPRITE_MAX_DATA);
}

void sprite_set_show(uint8_t index, bool show)
{
	m_sprites[index].show = show;
}

const sprite_t *sprite_get(uint8_t index)
{
	if (index < SPRITE_MAX_INDEX)
		return &m_sprites[index];
	else
		return NULL;
}