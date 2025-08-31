#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

typedef enum { INFO, WARNING, ERROR } LogLevel;
void log_message(LogLevel level, const char *format, ...);

#endif // LOGGER_H
