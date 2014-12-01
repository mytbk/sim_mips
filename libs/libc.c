int write(int fd, char *s, int len);

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

