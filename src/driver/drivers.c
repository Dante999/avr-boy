#include "i2cmaster.h"
#include "pcf8574.h"
#include "spislave.h"
#include "uart.h"

#define INIT_START(name) uart_puts(name);
#define INIT_DONE        uart_putsln("DONE!");

void drivers_init(void)
{
	uart_init();
	uart_putsln("");
	uart_putsln("----------------------------------");
	uart_putsln("|          AVR BOY               |");
	uart_putsln("----------------------------------");
	uart_putsln("UART initialized!");
	uart_putsln("loading other modules...");

	INIT_START("   I2C .......")
	i2c_init();
	INIT_DONE

	INIT_START("   PCF8574 ...")
	pcf8574_init();
	INIT_DONE

	INIT_START("   SPI .......")
	spi_init();
	INIT_DONE
}
