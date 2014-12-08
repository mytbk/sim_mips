#include "file.h"
#include "libs.h"
#include <fcntl.h>

#define PERMS 0666

FILE _iob[OPEN_MAX] = {
    { 0, (char*)0, (char*)0, _READ, 0 },
    { 0, (char*)0, (char*)0, _WRITE, 1 },
    { 0, (char*)0, (char*)0, _WRITE|_UNBUF, 2 }
};
        
static inline int
_creat(const char *path, int mode)
{
    return open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
}

FILE
*fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp=_iob; fp<_iob+OPEN_MAX; fp++) {
        if ((fp->flag & (_READ|_WRITE))==0) {
            break;
        }
    }

    if (fp>=_iob+OPEN_MAX) {
        return NULL;
    }

    if (*mode=='w') {
        fd = _creat(name, PERMS);
    } else if (*mode=='a') {
        if ((fd=open(name, O_WRONLY, 0))==-1) {
            fd = _creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_WRONLY, 0);
    }

    if (fd==-1) {
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode=='r')?_READ:_WRITE;
    return fp;
}

int
fwrite(const void *ptr, unsigned long size, unsigned long nmemb, FILE *stream)
{
    return write(stream->fd, (char*)ptr, size*nmemb);
}

    

    










