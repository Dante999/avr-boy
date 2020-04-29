#include <avr/io.h>

#include "i2cmaster.h"
#include "pcf8574.h"

#define PCF8574A_ADDRESS 0x70

void pcf8574_init(void)
{
	pcf8574_set(0xFF);
}

void pcf8574_set(uint8_t byte)
{
	i2c_start_wait(PCF8574A_ADDRESS + I2C_WRITE);
	i2c_write(byte);
	i2c_write(byte); // must be written twice
	i2c_stop();
}

uint8_t pcf8574_get(void)
{
	i2c_start_wait(PCF8574A_ADDRESS + I2C_READ);
	uint8_t a = i2c_read(1);
	uint8_t b = i2c_read(0); // must be read twice

	return b;
}
