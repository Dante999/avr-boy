/*******************************************************************************
 *
 * File    : uart.h
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
#include <avr/io.h>

#ifndef UART_H_
#	define UART_H_

//#define UART_BUFFER_SIZE 50

class Uart {

      public:
	static const uint8_t BUFFER_SIZE = 50;

	static volatile uint8_t g_buffer_complete;
	static volatile uint8_t g_buffer_index;
	static volatile char    g_buffer[BUFFER_SIZE];

      public:
	Uart(void) = delete;
	static void    init_hw(void);
	static void    send_c(char c);
	static void    send_s(const char *s);
	static void    send_ln(const char *s);
	static void    send_ui8(uint8_t i);
	static uint8_t is_complete(void);
	static void    read_buffer(char *buffer);
};

#endif
