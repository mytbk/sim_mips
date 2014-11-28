#include "syscall.h"
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void sys_uname(struct mips_regs *r, struct mmu *m)
{
    struct utsname *name = (struct utsname*)mmu_translate_addr(m, CALLARG(r, 0));
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

void
sys_open(struct mips_regs *r, struct mmu *m)
{
    uint32_t flags = CALLARG(r, 1);
    uint32_t mode = CALLARG(r, 2);
    char *fn = (char*)mmu_translate_addr(m, CALLARG(r, 0));
    CALLRET(r) = open(fn, flags, mode);
    CALLSTATE(r) = 0;
}

void
handle_syscall(struct mips_regs *r, struct mmu *m)
{
    fprintf(stderr, "syscall %d pc=0x%x\n", r->regs[2], r->pc);
    
    switch (r->regs[2]) {
    case 4005:
        sys_open(r, m);
        break;
        
    case 4045:
        sys_brk(r, m);
        break;
        
    case 4122: // sys_newuname
        sys_uname(r, m);
        break;
        
    default:
        fprintf(stderr, "syscall %d unhandled\n", r->regs[2]);
        break;
        
    }
}
