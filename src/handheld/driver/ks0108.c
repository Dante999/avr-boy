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

#define LCD_STATUS_BUSY  (1 << 7) // 0 = lcd is idle  | 1 = lcd is busy      |
#define LCD_STATUS_OFF   (1 << 5) // 0 = lcd is on    | 1 = lcd is off       |
#define LCD_STATUS_RESET (1 << 4) // 0 = lcd is ready | 1 = lcd is resetting |

#define LCD_WIDTH  128
#define LCD_HEIGHT 64
#define LCD_SIZE   (LCD_HEIGHT * LCD_WIDTH / 8)

#define LCD_CMD_SET_Y 0x40
#define LCD_CMD_SET_X 0xB8

#define LCD_ONOFF      0x3E
#define LCD_SET_ADDR   0x40
#define LCD_SET_PAGE   0xB8
#define LCD_DISP_START 0xC0

#define CSEL_1    1
#define CSEL_2    2
#define CSEL_NONE 3

static uint8_t ks0108_readstatus(uint8_t chip);

inline static void ks0108_delay(void)
{
	__asm("nop");
	__asm("nop");
	__asm("nop");
}

/*******************************************************************************
 * @brief   selects the given chip
 *
 * @param   chip   the chip which should be selected (use CSEL_1, CSEL_2 or
 *                 CSEL_NONE)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_chipselect(uint8_t chip)
{

	switch (chip) {

	case CSEL_1:
		LCD_PORTX_CS1 |= LCD_BIT_CS1;
		LCD_PORTX_CS2 &= ~LCD_BIT_CS2;
		break;

	case CSEL_2:
		LCD_PORTX_CS1 &= ~LCD_BIT_CS1;
		LCD_PORTX_CS2 |= LCD_BIT_CS2;
		break;

	case CSEL_NONE:
		LCD_PORTX_CS1 &= ~LCD_BIT_CS1;
		LCD_PORTX_CS2 &= ~LCD_BIT_CS2;
		break;

	default:
		LCD_PORTX_CS1 &= ~LCD_BIT_CS1;
		LCD_PORTX_CS2 &= ~LCD_BIT_CS2;
		break;
	}
}

/*******************************************************************************
 * @brief   write the given data to the 8bit lcd bus
 *
 * This write operation includes the handling of the enable pin, which means
 * after calling this method, the enable pin is set to low. Keep also in mind
 * that before calling this method, the corresponding chip should be selected
 * and AND the lcd is not busy.
 *
 * @param   data   the byte which should be written to the lcd bus
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_writedatabus(uint8_t data)
{
	LCD_DDRX_DATA  = 0xFF; // output
	LCD_PORTX_DATA = data; // min 450ns

	LCD_PORTX_ENABLE |= LCD_BIT_ENABLE;
	ks0108_delay();

	LCD_PORTX_ENABLE &= ~LCD_BIT_ENABLE;
	ks0108_delay();

	ks0108_chipselect(CSEL_NONE);
}

/*******************************************************************************
 * @brief   read the 8bit lcd bus
 *
 * This read operation includes the handling of the enable pin, which means
 * after calling this method, the enable pin is set to low. Keep also in mind
 * that before calling this method, the corresponding chip should be selected
 * AND the lcd is not busy.
 *
 * @param   none
 *
 * @return  the current value of the data bus
 *
 ******************************************************************************/
static uint8_t ks0108_readdatabus(void)
{
	LCD_DDRX_DATA  = 0x00; // input
	LCD_PORTX_DATA = 0xFF; // pullups

	LCD_PORTX_ENABLE |= LCD_BIT_ENABLE;
	ks0108_delay();

	uint8_t data = LCD_PINX_DATA;

	LCD_PORTX_ENABLE &= ~LCD_BIT_ENABLE;
	ks0108_delay();

	ks0108_chipselect(CSEL_NONE);

	return data;
}

/*******************************************************************************
 * @brief   writes the given command to the lcd
 *
 * The method also performs a busy check of the lcd and stays in a loop until
 * the lcd is ready to receive the command.
 *
 * @param   cmd    the command itself
 * @param   chip   selection of the chip
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_writecmd(uint8_t cmd, uint8_t chip)
{
	while (ks0108_readstatus(chip) & LCD_STATUS_BUSY) {
	};

	LCD_PORTX_DI &= ~LCD_BIT_DI;
	LCD_PORTX_RW &= ~LCD_BIT_RW;

	ks0108_chipselect(chip);
	ks0108_writedatabus(cmd);
}

/*******************************************************************************
 * @brief   writes the given data to the lcd
 *
 * The method also performs a busy check of the lcd and stays in a loop until
 * the lcd is ready to receive the data.
 *
 * @param   data   the data itself
 * @param   chip   selection of the chip
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_writedata(uint8_t data, uint8_t chip)
{
	while (ks0108_readstatus(chip) & LCD_STATUS_BUSY) {
	};

	LCD_PORTX_DI |= LCD_BIT_DI;
	LCD_PORTX_RW &= ~LCD_BIT_RW;

	ks0108_chipselect(chip);
	ks0108_writedatabus(data);
}

/*******************************************************************************
 * @brief   writes the given data to the lcd
 *
 * The method also performs a busy check of the lcd and stays in a loop until
 * the lcd is ready to receive the data.
 *
 * @param   data   the data itself
 * @param   chip   selection of the chip
 *
 * @return  none
 *
 ******************************************************************************/
static uint8_t ks0108_readdata(uint8_t chip)
{
	while (ks0108_readstatus(chip) & LCD_STATUS_BUSY) {
	};

	LCD_PORTX_DI |= LCD_BIT_DI;
	LCD_PORTX_RW |= LCD_BIT_RW;

	ks0108_chipselect(chip);
	return ks0108_readdatabus();
}

/*******************************************************************************
 * @brief   sets the address register pointer of the lcd
 *
 * Values greater than 63 will automatically cut of by a bitmask
 *
 * @param   addr   the number of the address (0-63)
 * @param   chip   the chip on which the addr should be set (CSEL_1 or CSEL_2)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_setaddr(uint8_t addr, uint8_t chip)
{
	uint8_t data = LCD_SET_ADDR | (0x3F & addr);

	ks0108_writecmd(data, chip);
}

/*******************************************************************************
 * @brief   sets the page address pointer of the lcd
 *
 * Values greater than 7 will automatically cut of by a bitmask
 *
 * @param   page   the number of the page (0-7)
 * @param   chip   the chip on which the page should be set (CSEL_1 or CSEL_2)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_setpage(uint8_t page, uint8_t chip)
{
	uint8_t data = LCD_SET_PAGE | (0x07 & page);

	ks0108_writecmd(data, chip);
}

/*******************************************************************************
 * @brief   sets the startline of the lcd
 *
 * Changing the startline is normally used shift the lcd pixel which creates a
 * scrolling effect
 *
 * @param   line   the new startline (0-63)
 * @param   chip   the chip on which the startline should be set (CSEL_1 or
 *                 CSEL_2)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_setstartline(uint8_t line, uint8_t chip)
{
	uint8_t data = LCD_DISP_START | (0x3F & line);

	ks0108_writecmd(data, chip);
}

/*******************************************************************************
 * @brief   sets the lcd on or off
 *
 * @param   on     use the values [1=on|0=off ]
 * @param   chip   the chip which should be set on or off (CSEL_1 or CSEL_2)
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_onoff(uint8_t on, uint8_t chip)
{
	uint8_t data = LCD_ONOFF | (0x01 & on);

	ks0108_writecmd(data, chip);
}

/*******************************************************************************
 * @brief   reads the status of the lcd
 *
 * Use the bitmasks #LCD_STATUS_BUSY #LCD_STATUS_OFF and #LCD_STATUS_RESET for
 * checking on the status byte
 *
 * @param   chip   the chip on which the status read should be performed
 *
 * @return  the read status byte
 *
 ******************************************************************************/
static uint8_t ks0108_readstatus(uint8_t chip)
{
	LCD_DDRX_DATA  = 0x00; // input
	LCD_PORTX_DATA = 0xFF; // pullups

	LCD_PORTX_RW |= LCD_BIT_RW;
	LCD_PORTX_DI &= ~LCD_BIT_DI;
	ks0108_chipselect(chip);

	ks0108_delay();

	uint8_t data = ks0108_readdatabus();

	return data;
}

/*******************************************************************************
 * @brief   sets the backlight on or off for the lcd
 *
 * @param   power   use 0 for disabling the backlight, all other values will
 *                  enable it
 *
 * @return  none
 *
 ******************************************************************************/
static void ks0108_backlight(uint8_t power)
{
	if (power)
		LCD_PORTX_BL |= LCD_BIT_BL;
	else
		LCD_PORTX_BL &= ~LCD_BIT_BL;
}

/*******************************************************************************
 * @brief   fills the whole lcd with the given pattern
 *
 * For not inverted lcds, using the pattern 0x00 will clear the complete display
 * where 0xFF will set it.
 *
 * @param   pattern   the pattern which will be used on the lcd
 *
 * @return  none
 *
 ******************************************************************************/
void ks0108_fillscreen(uint8_t pattern)
{

	uint8_t addr = 0; // 0-63
	uint8_t page = 0; // 0-7

	for (page = 0; page < 8; page++) {

		ks0108_setpage(page, CSEL_1);
		ks0108_setpage(page, CSEL_2);

		ks0108_setaddr(0, CSEL_1);
		ks0108_setaddr(0, CSEL_2);

		for (addr = 0; addr < 64; addr++) {
			ks0108_writedata(pattern, CSEL_1);
			ks0108_writedata(pattern, CSEL_2);
		}
	}
}

/*******************************************************************************
 * @brief   initializes the ks0108 lcd
 *
 * This method should be called before anything other in this module
 *
 * @param   none
 *
 * @return  none
 *
 ******************************************************************************/
void ks0108_init(void)
{
	LCD_DDRX_RESET |= LCD_BIT_RESET;
	LCD_PORTX_RESET &= ~LCD_BIT_RESET; // reset low
	_delay_ms(500);

	LCD_DDRX_BL |= LCD_BIT_BL;
	LCD_DDRX_DI |= LCD_BIT_DI;
	LCD_DDRX_RW |= LCD_BIT_RW;
	LCD_DDRX_CS1 |= LCD_BIT_CS1;
	LCD_DDRX_CS2 |= LCD_BIT_CS2;
	LCD_DDRX_ENABLE |= LCD_BIT_ENABLE;
	LCD_DDRX_DATA  = 0x00; // input
	LCD_PORTX_DATA = 0xFF; // pullups on

	LCD_PORTX_ENABLE &= ~LCD_BIT_ENABLE; // enable low
	LCD_PORTX_RW &= ~LCD_BIT_RW;         // write mode
	LCD_PORTX_CS1 &= ~LCD_BIT_CS1;
	LCD_PORTX_CS2 &= ~LCD_BIT_CS2;

	LCD_PORTX_RESET |= LCD_BIT_RESET; // reset high

	ks0108_backlight(1);
	ks0108_onoff(1, CSEL_1);
	ks0108_onoff(1, CSEL_2);

	ks0108_setstartline(0, CSEL_1);
	ks0108_setstartline(0, CSEL_2);

	ks0108_fillscreen(0x00);
}

void ks0108_drawbuffer(uint8_t *buffer)
{
	for (uint8_t page = 0; page < 8; page++) {

		for (uint8_t addr = 0; addr < 128; addr++) {

			const uint8_t csel = (addr < 64) ? CSEL_1 : CSEL_2;

			ks0108_setpage(page, csel);
			ks0108_setaddr(addr, csel);
			ks0108_writedata(*buffer, csel);

			buffer++;
		}
	}
}

void ks0108_scroll(uint8_t line)
{
	ks0108_setstartline(line, CSEL_1);
	ks0108_setstartline(line, CSEL_2);
}

void ks0108_draw_byte(uint8_t page, uint8_t addr, uint8_t length, uint8_t *byte)
{
	uint8_t csel = (addr < 64) ? CSEL_1 : CSEL_2;

	ks0108_setpage(page, csel);
	ks0108_setaddr(addr, csel);

	for (uint8_t i = 0; i < length; i++) {
		ks0108_writedata(byte[i], csel);
	}
}

void ks0108_set_pixel(uint8_t x, uint8_t y, uint8_t on)
{
	uint8_t csel = (x < 64) ? CSEL_1 : CSEL_2;
	uint8_t addr = x % 64;
	uint8_t page = y / 8;
	uint8_t bit  = y % 8;

	ks0108_setpage(page, csel);
	ks0108_setaddr(addr, csel);

	(void)ks0108_readdata(csel);
	uint8_t data = ks0108_readdata(csel);

	if (on) {
		data |= (1 << bit);
	}
	else {
		data &= ~(1 << bit);
	}

	ks0108_setaddr(addr, csel);
	ks0108_writedata(data, csel);
}
