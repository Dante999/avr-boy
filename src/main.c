#include <avr/io.h>

#include "button.h"
#include "i2cmaster.h"
#include "pcf8574.h"
#include "uart.h"
#include <util/delay.h>

static void init(void)
{
	i2c_init();
	uart_init();
}

static void debug_buttons(void)
{
	button_read();

	if (button_pressed(BUTTON_UP)) {
		uart_puts("BUTTON_UP ");
	}

	if (button_pressed(BUTTON_DOWN)) {
		uart_puts("BUTTON_DOWN ");
	}

	if (button_pressed(BUTTON_LEFT)) {
		uart_puts("BUTTON_LEFT ");
	}

	if (button_pressed(BUTTON_RIGHT)) {
		uart_puts("BUTTON_RIGHT ");
	}

	if (button_pressed(BUTTON_A)) {
		uart_puts("BUTTON_A ");
	}

	if (button_pressed(BUTTON_B)) {
		uart_puts("BUTTON_B ");
	}

	if (button_pressed(BUTTON_START)) {
		uart_puts("BUTTON_START ");
	}

	if (button_pressed(BUTTON_SELECT)) {
		uart_puts("BUTTON_SELECT ");
	}

	if (button_pressed(BUTTON_CONFIG)) {
		uart_puts("BUTTON_CONFIG ");
	}

	uart_putsln("");
}

int main(void)
{
	init();

	uart_putsln("initialization done!");

	button_init();

	while (1) {
		_delay_ms(100);

		debug_buttons();
	}
}
