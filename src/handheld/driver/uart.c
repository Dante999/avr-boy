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
#include "uart.h"

#include <avr/io.h>
#include <stdio.h>

#ifndef F_CPU
#	error F_CPU is not defined!!
#endif

// target Baudrate
#define BAUD 19200UL

// value for the UBRR Register
#define UBRR_VAL ((F_CPU + BAUD * 8) / (BAUD * 16) - 1)

// real Baudrate
#define BAUD_REAL (F_CPU / (16 * (UBRR_VAL + 1)))

// error Rate in promille, 1000 = 0K
#define BAUD_ERROR ((BAUD_REAL * 1000) / BAUD)

// check if the baudrate error is in range
#if ((BAUD_ERROR < 990) || (BAUD_ERROR > 1010))
#	error Rate of Baudrate Errors greater than 1%! Change system-clock or baudrate!
#endif

/*******************************************************************************
 * @brief initializes the uart interface
 *
 * @param  none
 *
 * @return none
 ******************************************************************************/
void uart_init()
{
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;

	UCSRB |= (1 << TXEN);                               // enable UART TX
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // asynchron 8N1
}

/*******************************************************************************
 * @brief prints single char to the uart interface
 *
 * @param  c     the char to print
 *
 * @return none
 ******************************************************************************/
void uart_putc(char c)
{

	while (!(UCSRA & (1 << UDRE))) {
		// waiting until sender is free...
	}

	UDR = c; // save character for sending
}

/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_putui(uint8_t i)
{
	char buffer[4];

	snprintf(buffer, 4, "%d", i);

	uart_puts(buffer);
}

/*******************************************************************************
 * @brief prints an 16-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_putui16(uint16_t i)
{
	char buffer[6];

	snprintf(buffer, 6, "%d", i);

	uart_puts(buffer);
}

/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_puti(int8_t i)
{
	char buffer[5];

	snprintf(buffer, 5, "%d", i);

	uart_puts(buffer);
}

/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_puti16(int8_t i)
{
	char buffer[7];

	snprintf(buffer, 7, "%d", i);

	uart_puts(buffer);
}

/*******************************************************************************
 * @brief prints a string to the uart interface (without any newline)
 *
 * @param  *s     pointer to the string which should be printed
 *
 * @return none
 ******************************************************************************/
void uart_puts(const char *s)
{
	while (*s != '\0') {
		uart_putc(*s);
		s++;
	}
}

/*******************************************************************************
 * @brief prints a string to the uart interface (with a newline)
 *
 * @param  *s     pointer to the string which should be printed
 *
 * @return none
 ******************************************************************************/
void uart_putsln(const char *s)
{
	uart_puts(s);
	uart_puts("\r\n");
}
