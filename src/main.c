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
	static struct Button button;

	button_read(&button);

	if (button.reg0 & BUTTON_REG0_UP) {
		uart_puts("BUTTON_UP ");
	}

	if (button.reg0 & BUTTON_REG0_DOWN) {
		uart_puts("BUTTON_DOWN ");
	}

	if (button.reg0 & BUTTON_REG0_LEFT) {
		uart_puts("BUTTON_LEFT ");
	}

	if (button.reg0 & BUTTON_REG0_RIGHT) {
		uart_puts("BUTTON_RIGHT ");
	}

	if (button.reg0 & BUTTON_REG0_A) {
		uart_puts("BUTTON_A ");
	}

	if (button.reg0 & BUTTON_REG0_B) {
		uart_puts("BUTTON_B ");
	}

	if (button.reg0 & BUTTON_REG0_START) {
		uart_puts("BUTTON_START ");
	}

	if (button.reg0 & BUTTON_REG0_SELECT) {
		uart_puts("BUTTON_SELECT ");
	}

	if (button.reg1 & BUTTON_REG1_CONFIG) {
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
