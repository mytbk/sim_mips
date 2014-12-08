/*
;  nasm -f elf cpuida.asm   for cpuida.o
;  gcc cpuidc.c -c          for cpuidc.o
;  gcc test.c cpuidc.o cpuida.o -lrt -lc -lm -o test
;  ./test
*/

#include <stdio.h>
#include "cpuidh.h"
#include <stdlib.h>     
#include <string.h> 
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

char    configdata[10][200];
char    timeday[30];
char    idString1[100] = " ";
char    idString2[100] = " ";
long theseSecs = 0;
long startSecs = 0;
long secs;
long millisecs;

int     megaHz;

int     pagesize;
 
#include <sys/sysinfo.h> 

/*
void local_time()
{
    time_t t;
    
    t = time(NULL);
    sprintf(timeday, "%s", asctime(localtime(&t)));
    return;
}
*/

struct timespec tp1;

void getSecs()
{
    clock_gettime(CLOCK_REALTIME, &tp1);
    
    theseSecs =  tp1.tv_sec;
    return;
}

void start_time()
{
    getSecs();
    startSecs = theseSecs;
    return;
}

void end_time()
{
    getSecs();
    secs = theseSecs - startSecs;
    millisecs = 1000 * secs;
    return;
}    
