#ifndef BALL_H
#define BALL_H

#include "core/core.h"
#include "spritelist.hpp"
#include <stdint.h>

class Ball {
      public:
	enum DIRECTION {
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_UPLEFT,
		DIR_UPRIGHT,
		DIR_DOWNLEFT,
		DIR_DOWNRIGHT
	};

	Ball(SpriteList::SPRITE_INDEX, uint8_t min_x, uint8_t max_x,
	     uint8_t min_y, uint8_t max_y);
	c_sprite_t *sprite(void);

	void move(uint8_t x, uint8_t y);
	void set_startdir(DIRECTION dir);
	void bounce(void);

      private:
	c_sprite_t *m_ballsprite;

	const uint8_t m_min_x;
	const uint8_t m_max_x;
	const uint8_t m_min_y;
	const uint8_t m_max_y;

	DIRECTION m_dir = DIR_UP;

	bool would_hit_left(void);
	bool would_hit_right(void);
	bool would_hit_top(void);
	bool would_hit_bot(void);

	void move_up(void);
	void move_down(void);
	void move_left(void);
	void move_right(void);
	void move_upleft(void);
	void move_upright(void);
	void move_downleft(void);
	void move_downright(void);
};

#endif // BALL_H
