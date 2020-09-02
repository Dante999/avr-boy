#include "spritelist.hpp"

c_sprite_t SpriteList::m_sprites[max_index];

c_sprite_t *SpriteList::get(const SpriteList::SPRITE_INDEX index)
{
	return &SpriteList::m_sprites[index];
}

void SpriteList::init()
{

	for (uint8_t i = 0; i < max_index; i++) {
		m_sprites[i].index = i;
	}
}
