static char buffer[1<<22];
static int nextfree=0;

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

