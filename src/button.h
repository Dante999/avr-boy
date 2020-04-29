#ifndef BUTTON_H
#define BUTTON_H

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

void    button_read(void);
uint8_t button_pressed(enum BUTTON button);
void    button_init(void);
#endif // BUTTON_H
