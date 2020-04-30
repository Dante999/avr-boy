#ifndef COREBUTTONS_H
#define COREBUTTONS_H

#include <avr/io.h>

enum BUTTON {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_START,
	BUTTON_SELECT,
	BUTTON_CONFIG
};

#define BUTTON_REG0_UP (1 << 0)
#define BUTTON_REG0_DOWN (1 << 1)
#define BUTTON_REG0_LEFT (1 << 2)
#define BUTTON_REG0_RIGHT (1 << 3)
#define BUTTON_REG0_A (1 << 4)
#define BUTTON_REG0_B (1 << 5)
#define BUTTON_REG0_START (1 << 6)
#define BUTTON_REG0_SELECT (1 << 7)
#define BUTTON_REG1_CONFIG (1 << 0)

struct Button {
	uint8_t reg0;
	uint8_t reg1;
};

#endif // COREBUTTONS_H
