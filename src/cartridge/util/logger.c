#include "logger.h"

#if LOG_LEVEL > LEVEL_OFF
#	include "driver/uart.hpp"

#endif

void log_print(const char *msg)
{
#if LOG_LEVEL > LEVEL_OFF
	Uart::send_s((char *)msg);
#endif
}

void log_println(const char *prefix, const char *msg)
{
#if LOG_LEVEL > LEVEL_OFF
	Uart::send_s(prefix);
	Uart::send_ln(msg);
#endif
}
