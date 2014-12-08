#include "printf.h"

int main()
{
    int i;
    
    puts("Hello, world!");
    printf("So great!\n");

    for (i=0; i<4; i++) {
        printf("i=%d\n", i);
    }
    
#ifdef FLOAT
    for (i=0; i<100; i++) {
        x = x+i;
    }
#endif
    return 0;
}

