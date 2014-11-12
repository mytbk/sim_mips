#ifndef SIM_SYSCALL
#define SIM_SYSCALL

#include "mips.h"
#include "mmu.h"

void sys_uname(struct mips_regs *, struct mmu *);

#endif
