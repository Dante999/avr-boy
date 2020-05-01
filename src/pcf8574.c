/*******************************************************************************
 *
 * avr-boy
 * Copyright (C) 2020 Matthias Escher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
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
