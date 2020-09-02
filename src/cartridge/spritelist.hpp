#ifndef SPRITELIST_H
#define SPRITELIST_H

#include "core/core.h"

class SpriteList {

      private:
	static constexpr uint8_t max_index = CORE_SPRITE_MAX_INDEX;

	static c_sprite_t m_sprites[max_index];

      public:
	enum SPRITE_INDEX {
		SPRITE_BALL1,
		SPRITE_BALL2,
		SPRITE_BALL3,
		SPRITE_BALL4,
		SPRITE_BALL5
	};

	static c_sprite_t *get(enum SPRITE_INDEX const index);

	static void init(void);
	SpriteList() = delete;
};

#endif // SPRITELIST_H
