#ifndef SIM_SYSCALL
#define SIM_SYSCALL

#include "mips.h"
#include "mmu.h"

#define SYSCALLNO(r) (r->regs[2]) // v0
#define CALLARG(r,n) (r->regs[(n)+4]) // a0-a7
#define CALLSTATE(r) (r->regs[7]) // a3
#define CALLRET(r) (r->regs[2]) // v0

void handle_syscall(struct mips_regs *, struct mmu *);
void sys_uname(struct mips_regs *, struct mmu *);
void sys_brk(struct mips_regs *, struct mmu *);
void sys_open(struct mips_regs *, struct mmu *);

#endif
