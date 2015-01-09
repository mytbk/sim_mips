#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

static FILE *ferr;

FILE *log_init(const char *fn)
{
    assert(ferr==NULL);
    ferr = fopen(fn, "w");
    return ferr;
}

void log_end()
{
    fclose(ferr);
}

void log_msg(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    vfprintf(ferr, format, arg);
    va_end(arg);
}










