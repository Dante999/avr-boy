#ifndef LOGGER_H
#define LOGGER_H

#define LEVEL_OFF     0
#define LEVEL_DEBUG   1
#define LEVEL_INFO    2
#define LEVEL_WARNING 3
#define LEVEL_SEVERE  4

#define LOG_LEVEL LEVEL_DEBUG

#if LOG_LEVEL > LEVEL_OFF
#	include "driver/uart.h"
#endif

#if (LOG_LEVEL <= LEVEL_INFO)
#	define LOG_INFO(msg) uart_putsln(msg)
#else
#	define LOG_INFO(msg) // msg
#endif

#endif // LOGGER_H
