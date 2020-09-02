#include "ball.hpp"

#include "spritelist.hpp"

Ball::Ball(SpriteList::SPRITE_INDEX index, uint8_t min_x, uint8_t max_x,
           uint8_t min_y, uint8_t max_y)
    : m_ballsprite(SpriteList::get(index)), m_min_x(min_x), m_max_x(max_x),
      m_min_y(min_y), m_max_y(max_y)
{
	m_ballsprite->show = true;

	m_ballsprite->data[0] = 0x3c;
	m_ballsprite->data[1] = 0x42;
	m_ballsprite->data[2] = 0x81;
	m_ballsprite->data[3] = 0x81;
	m_ballsprite->data[4] = 0x81;
	m_ballsprite->data[5] = 0x81;
	m_ballsprite->data[6] = 0x42;
	m_ballsprite->data[7] = 0x3c;
}

void Ball::set_coord(uint8_t x, uint8_t y)
{
	m_ballsprite->coord.x = x;
	m_ballsprite->coord.y = y;
}

void Ball::set_startdir(Ball::DIRECTION dir)
{
	m_dir = dir;
}

void Ball::bounce()
{
	switch (m_dir) {

	case DIR_UP:
		move_up();
		break;

	case DIR_DOWN:
		move_down();
		break;

	case DIR_LEFT:
		move_left();
		break;

	case DIR_RIGHT:
		move_right();
		break;

	case DIR_UPLEFT:
		move_upleft();
		break;

	case DIR_UPRIGHT:
		move_upright();
		break;

	case DIR_DOWNLEFT:
		move_downleft();
		break;

	case DIR_DOWNRIGHT:
		move_downright();
		break;
	}
}

bool Ball::poke_up()
{
	uint8_t &y = m_ballsprite->coord.y;

	if (y > m_min_y) {
		y--;
		return true;
	}
	else {
		y++;
		return false;
	}
}

bool Ball::poke_down()
{
	uint8_t &y = m_ballsprite->coord.y;

	if (y < m_max_y) {
		y++;
		return true;
	}
	else {
		y--;
		return false;
	}
}

bool Ball::poke_left()
{
	uint8_t &x = m_ballsprite->coord.x;

	if (x > m_min_x) {
		x--;
		return true;
	}
	else {
		x++;
		return false;
	}
}

bool Ball::poke_right()
{
	uint8_t &x = m_ballsprite->coord.x;

	if (x < m_max_x) {
		x++;
		return true;
	}
	else {
		x--;
		return false;
	}
}

c_sprite_t *Ball::sprite()
{
	return m_ballsprite;
}

void Ball::move_up(void)
{
	if (!poke_up()) {
		m_dir = DIR_DOWN;
	}
}

void Ball::move_down(void)
{
	if (!poke_down()) {
		m_dir = DIR_UP;
	}
}

void Ball::move_left(void)
{
	if (!poke_left()) {
		m_dir = DIR_RIGHT;
	}
}
void Ball::move_right(void)
{
	if (!poke_right()) {
		m_dir = DIR_LEFT;
	}
}

void Ball::move_upleft()
{
	bool hit_top  = !poke_up();
	bool hit_left = !poke_left();

	if (hit_top && hit_left) {
		m_dir = DIR_DOWNRIGHT;
	}
	else if (hit_top) {
		m_dir = DIR_DOWNLEFT;
	}
	else if (hit_left) {
		m_dir = DIR_UPRIGHT;
	}
}

void Ball::move_upright()
{
	bool hit_top   = !poke_up();
	bool hit_right = !poke_right();

	if (hit_top && hit_right) {
		m_dir = DIR_DOWNLEFT;
	}
	else if (hit_top) {
		m_dir = DIR_DOWNRIGHT;
	}
	else if (hit_right) {
		m_dir = DIR_UPLEFT;
	}
}

void Ball::move_downleft()
{
	bool hit_bot  = !poke_down();
	bool hit_left = !poke_left();

	if (hit_bot && hit_left) {
		m_dir = DIR_UPRIGHT;
	}
	else if (hit_bot) {
		m_dir = DIR_UPLEFT;
	}
	else if (hit_left) {
		m_dir = DIR_DOWNRIGHT;
	}
}

void Ball::move_downright()
{
	bool hit_bot   = !poke_down();
	bool hit_right = !poke_right();

	if (hit_bot && hit_right) {
		m_dir = DIR_UPLEFT;
	}
	else if (hit_bot) {
		m_dir = DIR_UPRIGHT;
	}
	else if (hit_right) {
		m_dir = DIR_DOWNLEFT;
	}
}
