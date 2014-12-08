#ifndef PRINTF_H
#define PRINTF_H

#include "file.h"
#include <stdarg.h>

int vsprintf(char *str, const char *format, va_list arg);
int sprintf(char *str, const char *format, ...);
int fprintf(FILE *stream, char *str, const char *format, ...);
int printf(const char *format, ...);

#endif
