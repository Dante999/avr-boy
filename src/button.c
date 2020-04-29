#include "button.h"

#include "pcf8574.h"

#define ROW0 (1 << 7)
#define ROW1 (1 << 6)
#define ROW2 (1 << 5)
#define COL0 (1 << 4)
#define COL1 (1 << 3)
#define COL2 (1 << 2)

static uint8_t reg = 0xFF;

static uint8_t stats_col0 = 0;
static uint8_t stats_col1 = 0;
static uint8_t stats_col2 = 0;

void button_init()
{
	pcf8574_set(reg);
}

void button_read()
{
	pcf8574_set(reg & ~COL0);
	stats_col0 = pcf8574_get();

	pcf8574_set(reg & ~COL1);
	stats_col1 = pcf8574_get();

	pcf8574_set(reg & ~COL2);
	stats_col2 = pcf8574_get();
}

uint8_t button_pressed(enum BUTTON button)
{
	uint8_t val = 0;

	switch (button) {

	case BUTTON_UP:
		val = (stats_col0 & ROW0);
		break;

	case BUTTON_DOWN:
		val = (stats_col0 & ROW1);
		break;

	case BUTTON_START:
		val = (stats_col0 & ROW2);
		break;

	case BUTTON_RIGHT:
		val = (stats_col1 & ROW0);
		break;

	case BUTTON_A:
		val = (stats_col1 & ROW1);
		break;

	case BUTTON_SELECT:
		val = (stats_col1 & ROW2);
		break;

	case BUTTON_LEFT:
		val = (stats_col2 & ROW0);
		break;

	case BUTTON_B:
		val = (stats_col2 & ROW1);
		break;

	case BUTTON_CONFIG:
		val = (stats_col2 & ROW2);
		break;
	}

	return val ? 0 : 1; // high active
}
