// assembly functions
int write(int fd, char *s, int len);

// for malloc()
char buffer[1<<22];
int nextfree=0;

int strlen(char *s)
{
    int l = 0;
    while (*s++) l++;
    return l;
}
        
int puts(char *s)
{
    int l = strlen(s);
    write(1, s, l);
    write(1, "\n", 1);
    return l+1;
}

void* malloc(unsigned long size)
{
    void* ret = buffer+nextfree;
    nextfree += (nextfree+size+4)&~3;
    return ret;
}

void free(void* addr)
{
    return;
}

int strcmp(char *s, char *t)
{
    while (*s && *s==*t) {
        s++;
        t++;
    }
    return *s-*t;
}

char* strcpy(char *dst, const char *src)
{
    char *ret = dst;
    while (*dst++=*src++)
        ;
    
    return ret;
}

void *memcpy(char *dst, char *src, unsigned long len)
{
    void *ret = (void*)dst;
    
    while (len) {
        *dst = *src;
        src++;
        dst++;
        len--;
    }
    return ret;
}










