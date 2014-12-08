#ifndef LIBS_H
#define LIBS_H

#include <time.h>

int write(int fd, char *s, int len);
int open(const char* path, int oflag, ...);
int strlen(char *s);
int strcmp(char *s, char *t);
char* strcpy(char *dst, const char *src);
int clock_gettime(unsigned, struct timespec *);

#endif
