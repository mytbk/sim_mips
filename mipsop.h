#ifndef SIM_MIPSOP_H
#define SIM_MIPSOP_H
#include "type.h"

#define DEFUN_R(fun,r,m,rs,rt,rd,shamt) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    int rs, int rt, int rd, int shamt)
#define DEFUN_I(fun,r,m,rs,rt,imm) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    int rs, int rt, uint32_t imm)
#define DEFUN_J(fun,r,m,imm) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    uint32_t imm)

#define OP3(op,rs,rt,rd) \
    regs->regs[rd] = regs->regs[rs] op regs->regs[rt]

#endif    
    
