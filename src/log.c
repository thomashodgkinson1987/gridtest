#include "log.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_message(LogLevel level, const char *format, ...)
{
    FILE *output_stream = stdout;

    switch (level)
    {
    case LOG_LEVEL_DEBUG:
    {
        output_stream = stdout;
        fprintf(output_stream, "[%s] ", "DEBUG");
        break;
    }
    case LOG_LEVEL_INFO:
    {
        output_stream = stdout;
        fprintf(output_stream, "[%s] ", "INFO");
        break;
    }
    case LOG_LEVEL_WARN:
    {
        output_stream = stderr;
        fprintf(output_stream, "[%s] ", "WARN");
        break;
    }
    case LOG_LEVEL_ERROR:
    {
        output_stream = stderr;
        fprintf(output_stream, "[%s] ", "ERROR");
        break;
    }
    case LOG_LEVEL_FATAL:
    {
        output_stream = stderr;
        fprintf(output_stream, "[%s] ", "FATAL");
        break;
    }
    default:
    {
        output_stream = stderr;
        fprintf(
            output_stream,
            "%s: Log level %d does not exist\n",
            __func__,
            level);
        break;
    }
    }

    va_list args;
    va_start(args, format);
    vfprintf(output_stream, format, args);
    va_end(args);

    fprintf(output_stream, "\n");

    if (level == LOG_LEVEL_FATAL)
    {
        exit(EXIT_FAILURE);
    }
}

void log_perror(const char *format, ...)
{
    va_list args_for_len;
    va_start(args_for_len, format);
    size_t len = vsnprintf(NULL, 0, format, args_for_len);
    va_end(args_for_len);

    char msg_buf[len + 1];

    va_list args_for_fmt;
    va_start(args_for_fmt, format);
    vsnprintf(msg_buf, sizeof(msg_buf), format, args_for_fmt);
    va_end(args_for_fmt);

    log_message(LOG_LEVEL_ERROR, "%s: %s", msg_buf, strerror(errno));
}

ATTR_NORETURN void log_fatal(const char *format, ...)
{
    va_list args_for_len;
    va_start(args_for_len, format);
    size_t len = vsnprintf(NULL, 0, format, args_for_len);
    va_end(args_for_len);

    char msg_buf[len + 1];

    va_list args_for_fmt;
    va_start(args_for_fmt, format);
    vsnprintf(msg_buf, sizeof(msg_buf), format, args_for_fmt);
    va_end(args_for_fmt);

    if (errno != 0)
    {
        log_message(LOG_LEVEL_FATAL, "%s: %s", msg_buf, strerror(errno));
    }
    else
    {
        log_message(LOG_LEVEL_FATAL, "%s", msg_buf);
    }

    // This line is technically unreachable but satisfies the compiler's
    // static analysis for the noreturn attribute.
    exit(EXIT_FAILURE);
}
