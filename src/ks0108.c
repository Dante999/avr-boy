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
#include "ks0108.h"

#include <util/delay.h>

#define BIT_SET(byte, bit)   (byte |= bit)
#define BIT_CLEAR(byte, bit) (byte &= ~bit)

#define LCD_CMD_ON    0x3F
#define LCD_CMD_OFF   0x3E
#define LCD_CMD_SET_Y 0x40
#define LCD_CMD_SET_X 0xB8

#define LCD_ONOFF      0x3E
#define LCD_SET_ADDR   0x40
#define LCD_SET_PAGE   0xB8
#define LCD_DISP_START 0xC0

#define CSEL_1 1
#define CSEL_2 2

static void ks0108_setdataline(uint8_t data)
{

	BIT_SET(LCD_PORTX_ENABLE, LCD_BIT_ENABLE); // min 140ns high

	_delay_us(1);
	LCD_PORTX_DATA = data; // min 450ns
	_delay_us(1);

	//	asm volatile("nop\n\t"
	//		     "nop\n\t"
	//		     "nop\n\t" ::);

	BIT_CLEAR(LCD_PORTX_ENABLE, LCD_BIT_ENABLE); // min 450ms
	_delay_us(1);
}

static void ks0108_chipselect(uint8_t chip)
{
	if (chip == CSEL_1) {
		BIT_SET(LCD_PORTX_CS1, LCD_BIT_CS1);
		BIT_CLEAR(LCD_PORTX_CS2, LCD_BIT_CS2);
	}
	else {
		BIT_CLEAR(LCD_PORTX_CS1, LCD_BIT_CS1);
		BIT_SET(LCD_PORTX_CS2, LCD_BIT_CS2);
	}
}

static void ks0108_writecmd(uint8_t cmd, uint8_t chip)
{
	BIT_CLEAR(LCD_PORTX_DI, LCD_BIT_DI);
	BIT_CLEAR(LCD_PORTX_RW, LCD_BIT_RW);

	ks0108_chipselect(chip);
	ks0108_setdataline(cmd);
}

static void ks0108_writedata(uint8_t data, uint8_t chip)
{
	BIT_SET(LCD_PORTX_DI, LCD_BIT_DI);
	BIT_CLEAR(LCD_PORTX_RW, LCD_BIT_RW);

	ks0108_chipselect(chip);
	ks0108_setdataline(data);
}

/*******************************************************************************
 * @brief   text
 *
 * @param   y   the Y address (0-63)
 * @param   chip the active chip (use CSEL_1 or CSEL_2)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_setaddr(uint8_t y, uint8_t chip)
{
	uint8_t data = LCD_SET_ADDR | (0x3F & y);

	ks0108_writecmd(data, chip);
}

/*******************************************************************************
 * @brief   text
 *
 * @param   page   the X address (0-7)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_setpage(uint8_t page, uint8_t chip)
{
	uint8_t data = LCD_SET_PAGE | (0x07 & page);

	ks0108_writecmd(data, chip);
}

static void ks0108_setstartline(uint8_t line, uint8_t chip)
{
	uint8_t data = LCD_DISP_START | (0x3F & line);

	ks0108_writecmd(data, chip);
}

static void ks0108_onoff(uint8_t on, uint8_t chip)
{
	uint8_t data = LCD_ONOFF | (0x01 & on);

	ks0108_writecmd(data, chip);
}

static void ks0108_backlight(uint8_t power)
{
	if (power)
		BIT_SET(LCD_PORTX_BL, LCD_BIT_BL);
	else
		BIT_CLEAR(LCD_PORTX_BL, LCD_BIT_BL);
}

void ks0108_fillscreen(uint8_t color)
{

	uint8_t add_y  = 0; // 0-63
	uint8_t page_x = 0; // 0-7

	for (page_x = 0; page_x < 8; page_x++) {

		ks0108_setpage(page_x, CSEL_1);
		ks0108_setpage(page_x, CSEL_2);

		ks0108_setaddr(0, CSEL_1);
		ks0108_setaddr(0, CSEL_2);

		for (add_y = 0; add_y < 64; add_y++) {

			ks0108_writedata(color, CSEL_1);
			ks0108_writedata(color, CSEL_2);
		}
	}
}

void ks0108_init(void)
{
	LCD_DDRX_BL |= LCD_BIT_BL;
	LCD_DDRX_DI |= LCD_BIT_DI;
	LCD_DDRX_RW |= LCD_BIT_RW;
	LCD_DDRX_CS1 |= LCD_BIT_CS1;
	LCD_DDRX_CS2 |= LCD_BIT_CS2;
	LCD_DDRX_RESET |= LCD_DDRX_RESET;
	LCD_DDRX_ENABLE |= LCD_BIT_ENABLE;
	LCD_DDRX_DATA |= 0xFF;

	LCD_PORTX_RESET &= ~LCD_BIT_RESET; // reset low

	LCD_PORTX_ENABLE &= ~LCD_BIT_ENABLE; // enable low
	LCD_PORTX_RW &= ~LCD_BIT_RW;         // write mode
	LCD_PORTX_CS1 &= ~LCD_BIT_CS1;
	LCD_PORTX_CS2 &= ~LCD_BIT_CS2;

	LCD_PORTX_RESET |= LCD_BIT_RESET; // reset low

	ks0108_backlight(1);
	ks0108_onoff(1, CSEL_1);
	ks0108_onoff(1, CSEL_2);
	ks0108_setstartline(0, CSEL_1);
	ks0108_setstartline(0, CSEL_2);

	ks0108_fillscreen(0x00);
}
