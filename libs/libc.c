#include "libs.h"

int puts(char *s)
{
    int l = strlen(s);
    write(1, s, l);
    write(1, "\n", 1);
    return l+1;
}

void niluse() 
{
    return;
}
