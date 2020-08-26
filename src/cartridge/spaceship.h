#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "core/core.h"

class Spaceship {

      private:
	c_sprite_t m_sprite_tl;
	c_sprite_t m_sprite_tr;
	c_sprite_t m_sprite_bl;
	c_sprite_t m_sprite_br;

      public:
	enum POSITION { POS_TOPLEFT, POS_TOPRIGHT, POS_BOTLEFT, POS_BOTRIGHT };
	Spaceship();
	void move(uint8_t x, uint8_t y);

	const c_sprite_t *get_sprite(enum POSITION pos);
};

#endif // SPACESHIP_H
