#include <avr/io.h>

#include "uart.h"

int main(void)
{
	uart_init();

	uart_putsln("avr-boy finished!");

	while (1) {
		uart_putsln("hello world!");
	}
}
