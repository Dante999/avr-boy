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
#include "uart.h"
#include <stdio.h>

#ifndef F_CPU
    #error F_CPU is not defined!!
#endif



#define BAUD 9600UL      // Target Baudrate

// Calculations (do not change)
#define UBRR_VAL    ((F_CPU+BAUD*8)/(BAUD*16)-1)    // Value for the UBRR Register
#define BAUD_REAL   (F_CPU/(16*(UBRR_VAL+1)))       // Real Baudrate
#define BAUD_ERROR  ((BAUD_REAL*1000)/BAUD)         // Error Rate in promille, 1000 = 0K

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
    #error Rate of Baudrate Errors greater than 1%! Change system-clock or baudrate!
#endif



/*******************************************************************************
 * @brief initializes the uart interface
 *
 * @param  none
 *
 * @return none
 ******************************************************************************/
void uart_init() {
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;

    UCSRB |= (1<<TXEN);                         // enable UART TX
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   // Asynchron 8N1
}


/*******************************************************************************
 * @brief prints single char to the uart interface
 *
 * @param  c     the char to print
 *
 * @return none
 ******************************************************************************/
void uart_putc(char c) {

    while (!(UCSRA & (1<<UDRE)))
    {
        // waiting until sender is free...
    }

    UDR = c;                                    // save character for sending
}


/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_putui(uint8_t i) {

    char buffer[4];

    sprintf(buffer, "%d", i);

    uart_puts(buffer);
}

/*******************************************************************************
 * @brief prints an 8-bit integer to the uart interface
 *
 * @param  i     the integer to print
 *
 * @return none
 ******************************************************************************/
void uart_puti(int8_t i) {

    char buffer[5];

    sprintf(buffer, "%d", i);

    uart_puts(buffer);
}


/*******************************************************************************
 * @brief prints a string to the uart interface (without any newline)
 *
 * @param  *s     pointer to the string which should be printed
 *
 * @return none
 ******************************************************************************/
void uart_puts(char *s) {

    while(*s != '\0') {
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
void uart_putsln(char *s) {
    uart_puts(s);
    uart_puts("\n");
}









