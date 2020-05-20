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
#ifndef KS0108_H
#define KS0108_H

#include <avr/io.h>

#include "graphx.h"

#define LCD_DDRX_DATA  DDRA
#define LCD_PORTX_DATA PORTA
#define LCD_PINX_DATA  PINA

#define LCD_DDRX_ENABLE  DDRB
#define LCD_PORTX_ENABLE PORTB
#define LCD_BIT_ENABLE   (1 << PB0)

#define LCD_DDRX_RW  DDRB
#define LCD_PORTX_RW PORTB
#define LCD_BIT_RW   (1 << PB1)

#define LCD_DDRX_DI  DDRB
#define LCD_PORTX_DI PORTB
#define LCD_BIT_DI   (1 << PB2)

#define LCD_DDRX_RESET  DDRB
#define LCD_PORTX_RESET PORTB
#define LCD_BIT_RESET   (1 << PB3)

#define LCD_DDRX_CS1  DDRD
#define LCD_PORTX_CS1 PORTD
#define LCD_BIT_CS1   (1 << PD2)

#define LCD_DDRX_CS2  DDRD
#define LCD_PORTX_CS2 PORTD
#define LCD_BIT_CS2   (1 << PD3)

#define LCD_DDRX_BL  DDRD
#define LCD_PORTX_BL PORTD
#define LCD_BIT_BL   (1 << PD4)

void ks0108_init(void);
void ks0108_fillscreen(uint8_t color);
void ks0108_drawgraphx(struct graphxdata *gdata);
void ks0108_testscreen(void);
// void ks0108_drawbuffer(uint8_t *buffer);

#endif // KS0108_H
