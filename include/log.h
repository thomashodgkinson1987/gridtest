#ifndef LOG_H
#define LOG_H

// Use the C11 standard noreturn if available
#if __STDC_VERSION__ >= 201112L
#include <stdnoreturn.h>
#define ATTR_NORETURN noreturn
// Fallback to GCC/Clang attribute
#elif defined(__GNUC__) || defined(__clang__)
#define ATTR_NORETURN __attribute__((noreturn))
// Otherwise, define it as empty
#else
#define ATTR_NORETURN
#endif

typedef enum log_level
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

void log_message(LogLevel level, const char *format, ...);
void log_perror(const char *format, ...);
ATTR_NORETURN void log_fatal(const char *format, ...);

#endif // LOG_H
