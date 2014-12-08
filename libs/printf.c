#include <stdarg.h>
#include "file.h"
#include "libs.h"

static char *digit = "0123456789abcdef";

static int
printnum(char *str, int base, int num)
{
    if (num<base) {
        *str = digit[num];
        return 1;
    } else {
        int cnt = printnum(str, base, num/base);
        str[cnt] = digit[num%base];
        return cnt+1;
    }
}

int
vsprintf(char *str, const char *format, va_list arg)
{
    char *base = str;
    int n;
    char *s;
    
    while (*format) {
        char c = *format;
        if (c!='%') {
            *str = c;
            str++;
            format++;
        } else {
            switch (format[1]) {
            case '%':
                *str = '%';
                str++;
                break;
            case 'd':
                n = va_arg(arg, int);
                str += printnum(str, 10, n);
                break;
            case 'x':
                n = va_arg(arg, int);
                str += printnum(str, 16, n);
                break;
            case 's':
                s = va_arg(arg, char*);
                while (*s) {
                    *str = *s;
                    str++;
                    s++;
                }
                break;
//            default:
//                while (1);
            }
            format += 2;
        }
    }
    return str-base;
}
    
int
sprintf(char *str, const char *format, ...)
{
    va_list arg;
    int ret;
    
    va_start(arg, format);
    ret = vsprintf(str, format, arg);
    va_end(arg);
    
    return ret;
}

int
fprintf(FILE *stream, const char *format, ...)
{
    va_list arg;
    int ret;
    char buf[BUFSIZ];
    
    va_start(arg, format);
    ret = vsprintf(buf, format, arg);
    va_end(arg);

    return write(stream->fd, buf, ret);
}

int
printf(const char *format, ...)
{
    va_list arg;
    int ret;
    char buf[BUFSIZ];
    
    va_start(arg, format);
    ret = vsprintf(buf, format, arg);
    va_end(arg);

    return write(1, buf, ret);
}



