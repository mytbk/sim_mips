#ifndef SIM_DEBUGGER_H
#define SIM_DEBUGGER_H

#include "mips.h"

void print_regs(struct mips_regs *);
int debugger(struct mips_regs *, struct mmu *);

#endif
