#include "userport.h"

#include <avr/io.h>

static void set_reg(volatile uint8_t *reg, uint8_t bit, uint8_t state)
{
	switch (state) {
	case USERPORT_LOW:
		*reg &= ~(1 << bit);
		break;

	case USERPORT_HIGH:
		*reg |= (1 << bit);
		break;

	case USERPORT_TOGGLE:
		*reg ^= (1 << bit);
	}
}

void userport_init(void)
{
	DDRD |= (1 << PD6);
	DDRC |= (1 << PC7);
}

void userport_11(uint8_t stat)
{
	set_reg(&PORTD, PD6, stat);
}

void userport_12(uint8_t stat)
{
	set_reg(&PORTC, PC7, stat);
}
