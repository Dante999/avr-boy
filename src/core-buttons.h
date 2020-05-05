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
#ifndef COREBUTTONS_H
#define COREBUTTONS_H

#include <avr/io.h>

#define BUTTON_REG0_UP     (1 << 0)
#define BUTTON_REG0_DOWN   (1 << 1)
#define BUTTON_REG0_LEFT   (1 << 2)
#define BUTTON_REG0_RIGHT  (1 << 3)
#define BUTTON_REG0_A      (1 << 4)
#define BUTTON_REG0_B      (1 << 5)
#define BUTTON_REG0_START  (1 << 6)
#define BUTTON_REG0_SELECT (1 << 7)
#define BUTTON_REG1_CONFIG (1 << 0)

struct Button {
	uint8_t reg0;
	uint8_t reg1;
};

#endif // COREBUTTONS_H
