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

void Ball::move(uint8_t x, uint8_t y)
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

bool Ball::would_hit_left()
{
	return !(m_ballsprite->coord.x > m_min_x);
}

bool Ball::would_hit_right()
{
	return !(m_ballsprite->coord.x < m_max_x);
}

bool Ball::would_hit_top()
{
	return !(m_ballsprite->coord.y < m_max_y);
}

bool Ball::would_hit_bot()
{
	return !(m_ballsprite->coord.y > m_min_y);
}

c_sprite_t *Ball::sprite()
{
	return m_ballsprite;
}

void Ball::move_up(void)
{
	uint8_t &y = m_ballsprite->coord.y;

	if (would_hit_top()) {
		m_dir = DIR_DOWN;
		y--;
	}
	else {
		y++;
	}
}

void Ball::move_down(void)
{
	uint8_t &y = m_ballsprite->coord.y;

	if (would_hit_bot()) {
		m_dir = DIR_UP;
		y++;
	}
	else {
		y--;
	}
}

void Ball::move_left(void)
{
	uint8_t &x = m_ballsprite->coord.x;

	if (would_hit_left()) {
		m_dir = DIR_RIGHT;
		x++;
	}
	else {
		x--;
	}
}
void Ball::move_right(void)
{
	uint8_t &x = m_ballsprite->coord.x;

	if (would_hit_right()) {
		m_dir = DIR_LEFT;
		x--;
	}
	else {
		x++;
	}
}

void Ball::move_upleft()
{
	uint8_t &x = m_ballsprite->coord.x;
	uint8_t &y = m_ballsprite->coord.y;

	// touches top-left corner
	if (would_hit_left() && would_hit_top()) {
		x++;
		y--;
		m_dir = DIR_DOWNRIGHT;
	}
	// touches only top-side
	else if (would_hit_top()) {
		x--;
		y--;
		m_dir = DIR_DOWNLEFT;
	}
	// touches only left-side
	else if (would_hit_left()) {
		x++;
		y++;
		m_dir = DIR_UPRIGHT;
	}
	else {
		x--;
		y++;
	}
}

void Ball::move_upright()
{
	uint8_t &x = m_ballsprite->coord.x;
	uint8_t &y = m_ballsprite->coord.y;

	// touches top-right corner
	if (would_hit_top() && would_hit_right()) {
		x--;
		y--;
		m_dir = DIR_DOWNLEFT;
	}
	// touches only top-side
	else if (would_hit_top()) {
		x++;
		y--;
		m_dir = DIR_DOWNRIGHT;
	}
	// touches only right-side
	else if (would_hit_right()) {
		x--;
		y++;
		m_dir = DIR_UPLEFT;
	}
	else {
		x++;
		y++;
	}
}

void Ball::move_downleft()
{
	uint8_t &x = m_ballsprite->coord.x;
	uint8_t &y = m_ballsprite->coord.y;

	// touches top-right corner
	if (would_hit_bot() && would_hit_right()) {
		x--;
		y++;
		m_dir = DIR_UPLEFT;
	}
	// touches only top-side
	else if (would_hit_bot()) {
		x++;
		y++;
		m_dir = DIR_UPRIGHT;
	}
	// touches only right-side
	else if (would_hit_left()) {
		x--;
		y--;
		m_dir = DIR_DOWNRIGHT;
	}
	else {
		x--;
		y--;
	}
}

void Ball::move_downright()
{
	uint8_t &x = m_ballsprite->coord.x;
	uint8_t &y = m_ballsprite->coord.y;

	// touches top-right corner
	if (would_hit_bot() && would_hit_right()) {
		x--;
		y++;
		m_dir = DIR_UPLEFT;
	}
	// touches only top-side
	else if (would_hit_bot()) {
		x++;
		y++;
		m_dir = DIR_UPRIGHT;
	}
	// touches only right-side
	else if (would_hit_right()) {
		x--;
		y--;
		m_dir = DIR_DOWNLEFT;
	}
	else {
		x++;
		y--;
	}
}
