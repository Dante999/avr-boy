#include "core.h"

#define BUTTON_REG0_UP     (1 << 0)
#define BUTTON_REG0_DOWN   (1 << 1)
#define BUTTON_REG0_LEFT   (1 << 2)
#define BUTTON_REG0_RIGHT  (1 << 3)
#define BUTTON_REG0_A      (1 << 4)
#define BUTTON_REG0_B      (1 << 5)
#define BUTTON_REG0_START  (1 << 6)
#define BUTTON_REG0_SELECT (1 << 7)
#define BUTTON_REG1_CONFIG (1 << 0)

bool core_button_get(struct button_stat *stat, enum button_id id)
{
	bool retval = false;

	switch (id) {

	case BUTTON_UP:
		retval = (stat->reg0 & BUTTON_REG0_UP) ? true : false;
		break;

	case BUTTON_DOWN:
		retval = (stat->reg0 & BUTTON_REG0_DOWN) ? true : false;
		break;

	case BUTTON_LEFT:
		retval = (stat->reg0 & BUTTON_REG0_LEFT) ? true : false;
		break;

	case BUTTON_RIGHT:
		retval = (stat->reg0 & BUTTON_REG0_RIGHT) ? true : false;
		break;

	case BUTTON_A:
		retval = (stat->reg0 & BUTTON_REG0_A) ? true : false;
		break;

	case BUTTON_B:
		retval = (stat->reg0 & BUTTON_REG0_B) ? true : false;
		break;

	case BUTTON_CONFIG:
		retval = (stat->reg1 & BUTTON_REG1_CONFIG) ? true : false;
		break;

	default:
		break;
	}

	return retval;
}

void core_button_set(struct button_stat *stat, enum button_id id)
{
	switch (id) {

	case BUTTON_UP:
		stat->reg0 |= BUTTON_REG0_UP;
		break;

	case BUTTON_DOWN:
		stat->reg0 |= BUTTON_REG0_DOWN;
		break;

	case BUTTON_LEFT:
		stat->reg0 |= BUTTON_REG0_LEFT;
		break;

	case BUTTON_RIGHT:
		stat->reg0 |= BUTTON_REG0_RIGHT;
		break;

	case BUTTON_A:
		stat->reg0 |= BUTTON_REG0_A;
		break;

	case BUTTON_B:
		stat->reg0 |= BUTTON_REG0_B;
		break;

	case BUTTON_CONFIG:
		stat->reg1 |= BUTTON_REG1_CONFIG;
		break;

	default:
		break;
	}
}

void core_button_clear(struct button_stat *stat)
{
	stat->reg0 = 0x00;
	stat->reg1 = 0x00;
}