/**
 * Copyright (C) 2020 dante999
 *
 * This file is part of avr-boy.
 *
 * avr-boy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * avr-boy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with avr-boy.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "system.h"
#include "uCUnit-v1.0.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void CHECK_u8_equals(uint8_t expected, uint8_t actual, const char *msg)
{
	char buffer[80];

	sprintf(buffer, "[expected=%d|actual=%d]", expected, actual);

	UCUNIT_Check(expected == actual, (char *)msg, buffer);
}