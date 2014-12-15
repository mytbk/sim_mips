#ifndef SIMERR_H
#define SIMERR_H

#include <stdio.h>

FILE *log_init();
void log_end();
void log_msg(const char *format, ...);

#endif



