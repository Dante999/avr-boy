#include "button.h"

#include "pcf8574.h"

#define ROW0 (1 << 7)
#define ROW1 (1 << 6)
#define ROW2 (1 << 5)
#define COL0 (1 << 4)
#define COL1 (1 << 3)
#define COL2 (1 << 2)

static uint8_t reg = 0xFF;

static void read_col0(struct Button *button, uint8_t col0)
{
	if (col0 & ROW0)
		button->reg0 |= BUTTON_REG0_UP;

	if (col0 & ROW1)
		button->reg0 |= BUTTON_REG0_DOWN;

	if (col0 & ROW2)
		button->reg0 |= BUTTON_REG0_START;
}

static void read_col1(struct Button *button, uint8_t col1)
{
	if (col1 & ROW0)
		button->reg0 |= BUTTON_REG0_RIGHT;

	if (col1 & ROW1)
		button->reg0 |= BUTTON_REG0_A;

	if (col1 & ROW2)
		button->reg0 |= BUTTON_REG0_SELECT;
}

static void read_col2(struct Button *button, uint8_t col2)
{
	if (col2 & ROW0)
		button->reg0 |= BUTTON_REG0_LEFT;

	if (col2 & ROW1)
		button->reg0 |= BUTTON_REG0_A;

	if (col2 & ROW2)
		button->reg1 |= BUTTON_REG1_CONFIG;
}

void button_init()
{
	pcf8574_set(reg);
}

void button_read(struct Button *button)
{
	button->reg0 = 0x00;
	button->reg1 = 0x00;

	pcf8574_set(reg & ~COL0);
	uint8_t col0 = ~pcf8574_get();

	pcf8574_set(reg & ~COL1);
	uint8_t col1 = ~pcf8574_get();

	pcf8574_set(reg & ~COL2);
	uint8_t col2 = ~pcf8574_get();

	read_col0(button, col0);
	read_col1(button, col1);
	read_col2(button, col2);
}
