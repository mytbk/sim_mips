#ifndef SIMERR_H
#define SIMERR_H

#include <stdio.h>

FILE *log_init(const char *fn);
FILE *trace_init(const char *fn);
void log_end();
void log_msg(const char *format, ...);
void trace_msg(const char *format, ...);

#endif



