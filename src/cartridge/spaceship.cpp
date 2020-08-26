#include "spaceship.h"

#include <string.h>

#define IMG_WIDTH  32
#define IMG_HEIGHT 32
#define IMG_SIZE   128

Spaceship::Spaceship()
{
	// 0x01, 0x41, 0x63, 0xe3, 0xf7, 0xff, 0xff, 0xfe, // top-left
	m_sprite_tl.index   = 0;
	m_sprite_tl.data[0] = 0x01;
	m_sprite_tl.data[1] = 0x41;
	m_sprite_tl.data[2] = 0x63;
	m_sprite_tl.data[3] = 0xe3;
	m_sprite_tl.data[4] = 0xf7;
	m_sprite_tl.data[5] = 0xff;
	m_sprite_tl.data[6] = 0xff;
	m_sprite_tl.data[7] = 0xfe;

	// 0xfc, 0xfc, 0xfc, 0xec, 0xc8, 0x88, 0x88, 0x80, // top-right
	m_sprite_tr.index   = 1;
	m_sprite_tr.data[0] = 0xfc;
	m_sprite_tr.data[1] = 0xfc;
	m_sprite_tr.data[2] = 0xfc;
	m_sprite_tr.data[3] = 0xec;
	m_sprite_tr.data[4] = 0xc8;
	m_sprite_tr.data[5] = 0x88;
	m_sprite_tr.data[6] = 0x88;
	m_sprite_tr.data[7] = 0x80;

	// 0x80, 0x82, 0xc6, 0xc7, 0xef, 0xff, 0xff, 0x7f, // bot-left
	m_sprite_bl.index   = 2;
	m_sprite_bl.data[0] = 0x80;
	m_sprite_bl.data[1] = 0x82;
	m_sprite_bl.data[2] = 0xc6;
	m_sprite_bl.data[3] = 0xc7;
	m_sprite_bl.data[4] = 0xef;
	m_sprite_bl.data[5] = 0xff;
	m_sprite_bl.data[6] = 0xff;
	m_sprite_bl.data[7] = 0x7f;

	// 0x3f, 0x3f, 0x3f, 0x37, 0x13, 0x11, 0x11, 0x01, // bot-right
	m_sprite_br.index   = 3;
	m_sprite_br.data[0] = 0x3f;
	m_sprite_br.data[1] = 0x3f;
	m_sprite_br.data[2] = 0x3f;
	m_sprite_br.data[3] = 0x37;
	m_sprite_br.data[4] = 0x13;
	m_sprite_br.data[5] = 0x11;
	m_sprite_br.data[6] = 0x11;
	m_sprite_br.data[7] = 0x01;
}

void Spaceship::move(uint8_t x, uint8_t y)
{
	m_sprite_tl.coord.x = x;
	m_sprite_tl.coord.y = y;

	m_sprite_tr.coord.x = x + 8;
	m_sprite_tr.coord.y = y;

	m_sprite_bl.coord.x = x;
	m_sprite_bl.coord.y = y + 8;

	m_sprite_br.coord.x = x + 8;
	m_sprite_br.coord.y = y + 8;
}

const c_sprite_t *Spaceship::get_sprite(Spaceship::POSITION pos)
{
	switch (pos) {
	case POS_TOPLEFT:
		return &m_sprite_tl;
	case POS_TOPRIGHT:
		return &m_sprite_tr;
	case POS_BOTLEFT:
		return &m_sprite_bl;
	case POS_BOTRIGHT:
		return &m_sprite_br;
	}

	return NULL;
}
