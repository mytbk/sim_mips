int strlen(char *s)
{
    int l = 0;
    while (*s++) l++;
    return l;
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
