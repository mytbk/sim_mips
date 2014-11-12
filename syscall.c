#include "mips.h"
#include "mmu.h"
#include <sys/utsname.h>
#include <string.h>

void sys_uname(struct mips_regs *r, struct mmu *m)
{
    uint32_t va = (struct utsname*)r->regs[4];
    struct utsname *name = (struct utsname*)mmu_translate_addr(m, va);
    strcpy(name->sysname, "Linux");
    strcpy(name->version, "3.10");
    strcpy(name->machine, "mipsel");
    r->regs[7] = 0;
    r->regs[2] = 0;
}

