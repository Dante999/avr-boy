/*******************************************************************************
 *
 * File    : uart.c
 *
 * Author  : Dante999
 * Date    : 28.12.2018
 *
 * Tabsize : 4
 * License : GNU GPL v2
 *
 * writes to the uart serial interface
 *
 *
 ******************************************************************************/
#include "uart.hpp"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#ifndef F_CPU
#	error F_CPU is not defined!
#endif

#define CR      "\r"
#define CRLF    "\r\n"
#define NEWLINE CRLF

volatile uint8_t Uart::g_buffer_complete = 0; // 1 .. String komplett empfangen
volatile uint8_t Uart::g_buffer_index    = 0;
volatile char    Uart::g_buffer[Uart::BUFFER_SIZE] = "";

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
void Uart::init_hw()
{
	UBRR0H = (uint8_t)UBRR_VAL >> 8;
	UBRR0L = (uint8_t)UBRR_VAL & 0xFF;

	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // enable UART TX
	UCSR0C = (1 << UCSZ01) |
	         (1 << UCSZ00); // Asynchron (8-bit)(no-parity)(1-stop-bit)
}

/*******************************************************************************
 * @brief prints single char to the uart interface
 *
 * @param  c     the char to print
 *
 * @return none
 ******************************************************************************/
void Uart::send_c(char c)
{
	while (!(UCSR0A & (1 << UDRE0))) {
		// waiting until sender is free...
	}

	UDR0 = c; // save character for sending
}

/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void Uart::send_ui8(uint8_t i)
{

	char buffer[4];

	sprintf(buffer, "%d", i);

	Uart::send_s(buffer);
}

/*******************************************************************************
 * @brief prints a string to the uart interface (without any newline)
 *
 * @param  *s     pointer to the string which should be printed
 *
 * @return none
 ******************************************************************************/
void Uart::send_s(const char *s)
{
	while (*s != '\0') {
		Uart::send_c(*s);
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
void Uart::send_ln(const char *s)
{
	Uart::send_s(s);
	Uart::send_s(NEWLINE);
}

uint8_t Uart::is_complete()
{
	return g_buffer_complete;
}

void Uart::read_buffer(char *buffer)
{
	memcpy(buffer, (void *)g_buffer, Uart::BUFFER_SIZE);

	g_buffer_complete = 0;
}

extern "C" {

void handle_received_char(unsigned char c)
{

	if (c == '\b' && Uart::g_buffer_index > 0) {
		Uart::g_buffer_index--;
		Uart::send_s("\b \b");
	}
	else if (c != '\r' && c != '\n' &&
	         Uart::g_buffer_index < Uart::BUFFER_SIZE - 1) {

		Uart::g_buffer[Uart::g_buffer_index] = c;
		Uart::g_buffer_index++;

		Uart::send_c(c);
	}
	else {
		Uart::g_buffer[Uart::g_buffer_index] = '\0';
		Uart::g_buffer_index                 = 0;
		Uart::g_buffer_complete              = 1;

		Uart::send_ln("");
	}
}

ISR(USART_RX_vect)
{

	unsigned char c = UDR0;

	if (!Uart::g_buffer_complete) {
		handle_received_char(c);
	}
}
}
