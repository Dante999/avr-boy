#include "userport.h"

#include <avr/io.h>

void userport_init(void)
{
	DDRD |= (1 << PD6);
	DDRC |= (1 << PC7);
}

void userport_11(bool high)
{
	if (high)
		PORTD |= (1 << PD6);
	else
		PORTD &= ~(1 << PD6);
}

void userport_12(bool high)
{
	if (high)
		PORTC |= (1 << PC7);
	else
		PORTC &= ~(1 << PC7);
}