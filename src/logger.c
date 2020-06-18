#include "logger.h"

#if LOG_LEVEL > LEVEL_OFF
#	include "driver/uart.h"
#endif

void log_print(const char *msg)
{
#if LOG_LEVEL > LEVEL_OFF
	uart_puts((char *)msg);
#endif
}

void log_println(const char *prefix, const char *msg)
{
#if LOG_LEVEL > LEVEL_OFF
	uart_puts((char *)prefix);
	uart_putsln((char *)msg);
#endif
}
