#ifndef LOGGER_H
#define LOGGER_H

#define LEVEL_OFF     0
#define LEVEL_DEBUG   1
#define LEVEL_INFO    2
#define LEVEL_WARNING 3
#define LEVEL_ERROR   4

#define LOG_LEVEL LEVEL_DEBUG

void log_print(const char *msg);
void log_println(const char *prefix, const char *msg);

#if (LOG_LEVEL <= LEVEL_DEBUG)
#	define LOG_DEBUG(msg) log_println("[D] ", msg);
#else
#	define LOG_DEBUG(msg)
#endif

#if (LOG_LEVEL <= LEVEL_INFO)
#	define LOG_INFO_LINE(msg) log_println("[I] ", msg);
#else
#	define LOG_INFO_LINE(msg)
#endif

#if (LOG_LEVEL <= LEVEL_WARNING)
#	define LOG_WARNING(msg) log_println("[W] ", msg);
#else
#	define LOG_WARNING(msg)
#endif

#if (LOG_LEVEL <= LEVEL_ERROR)
#	define LOG_ERROR(msg) log_println("[E] ", msg);
#else
#	define LOG_ERROR(msg)
#endif

#endif // LOGGER_H
