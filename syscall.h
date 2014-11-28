#ifndef SIM_SYSCALL
#define SIM_SYSCALL

#include "mips.h"
#include "mmu.h"

#define SYSCALLNO(r) (r->regs[2])
#define CALLARG(r,n) (r->regs[(n)+4])
#define CALLSTATE(r) (r->regs[7])
#define CALLRET(r) (r->regs[2])

void sys_uname(struct mips_regs *, struct mmu *);
void sys_brk(struct mips_regs *, struct mmu *);

#endif
