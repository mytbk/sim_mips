#include "syscall.h"
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>

void sys_uname(struct mips_regs *r, struct mmu *m)
{
    uint32_t va = (struct utsname*)CALLARG(r,0);
    struct utsname *name = (struct utsname*)mmu_translate_addr(m, va);
    strcpy(name->sysname, "Linux");
    strcpy(name->version, "3.10");
    strcpy(name->machine, "mipsel");
    CALLSTATE(r) = 0;
    CALLRET(r) = 0;
}

void sys_brk(struct mips_regs *r, struct mmu *m)
{
    fprintf(stderr, "sys_brk: %x\n", CALLARG(r, 0));
    
    CALLRET(r) = mmu_set_brk(m, m->brk+CALLARG(r,0));
    CALLSTATE(r) = 0;
}
