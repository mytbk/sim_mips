#ifndef LIBS_H
#define LIBS_H

int write(int fd, char *s, int len);
int open(const char* path, int oflag, ...);
int strlen(char *s);

#endif
