#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

static FILE *ferr;
static FILE *ftrace;

FILE *log_init(const char *fn)
{
    assert(ferr==NULL);
    ferr = fopen(fn, "w");
    return ferr;
}

FILE *trace_init(const char *fn)
{
    assert(ftrace==NULL);
    ftrace = fopen(fn, "w");
    return ftrace;
}

void log_end()
{
    fclose(ferr);
    if (ftrace) {
        fclose(ftrace);
    }
}

void log_msg(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    vfprintf(ferr, format, arg);
    va_end(arg);
}

void trace_msg(const char *format, ...)
{
    if (!ftrace) {
        return;
    }
    
    va_list arg;
    va_start(arg, format);
    vfprintf(ftrace, format, arg);
    va_end(arg);
}

