#include "type.h"
#include "mips.h"
#include "mmu.h"
#include "mipsop.h"

DEFUN_R(add, regs, m, rs, rt, rd, sh)
{
    OP3(+,rs,rt,rd);
}

DEFUN_R(addu, regs, m, rs, rt, rd, sh)
{
    OP3(+,rs,rt,rd);
}

DEFUN_R(sub, regs, m, rs, rt, rd, sh)
{
    OP3(-,rs,rt,rd);
}

DEFUN_R(subu, regs, m, rs, rt, rd, sh)
{
    OP3(-,rs,rt,rd);
}

DEFUN_R(and, regs, m, rs, rt, rd, sh)
{
    OP3(&,rs,rt,rd);
}

DEFUN_R(or, regs, m, rs, rt, rd, sh)
{
    OP3(|,rs,rt,rd);
}

DEFUN_R(nor, regs, m, rs, rt, rd, sh)
{
    OP3(|, rs, rt, rd);
    regs->regs[rd] = ~regs->regs[rd];
}

DEFUN_R(xor, regs, m, rs, rt, rd, sh)
{
    OP3(^, rs, rt, rd);
}

DEFUN_R(slt, regs, m, rs, rt, rd, sh)
{
    int x = regs->regs[rs];
    int y = regs->regs[rt];
    regs->regs[rd] = (x<y)?1:0;
}

DEFUN_R(sltu, regs, m, rs, rt, rd, sh)
{
    OP3(<, rs, rt, rd);
}

DEFUN_R(sll, regs, m, rs, rt, rd, shamt)
{
    regs->regs[rd] = regs->regs[rt]<<shamt;
}

DEFUN_R(srl, regs, m, rs, rt, rd, shamt)
{
    regs->regs[rd] = regs->regs[rt]>>shamt;
}

r_inst_tab mips_r_insts[] =
{
    [MR_SLL] { sll, "sll $%d, $%d, %d" },
    [MR_SRL] { srl, "srl $%d, $%d, %d" },
    [MR_ADD] { add, "add $%d, $%d, $%d" },
    [MR_ADDU] { addu, "addu $%d, $%d, $%d" },
    [MR_SUB] { sub, "sub $%d, $%d, $%d" },
    [MR_SUBU] { subu, "subu $%d, $%d $%d" },
    [MR_AND] { and, "and $%d, $%d, $%d" },
    [MR_OR] { or, "or $%d, $%d, $%d" },
    [MR_XOR] { xor, "xor $%d, $%d, $%d" },
    [MR_NOR] { nor, "nor $%d, $%d, $%d" },
    [MR_SLT] { slt, "slt $%d, $%d, $%d" },
    [MR_SLTU] { sltu, "sltu $%d, $%d, $%d" }
};
        
// R instruction format
// opcode[26:31]=0 rs[21:25] rt[16:20] rd[11:15] shamt[6:10] funct[1:5]
void
r_inst(struct mips_regs *reg, struct mmu *m, int rs, int rt, int rd,
       int shamt, int funct)
{
    if (mips_r_insts[funct]) {
        mips_r_insts[funct].exec_r_inst(reg, m, rs, rt, rd, shamt);
    }
}

// I instruction format
// opcode[26:31] rs[21:25] rt[16:20] imm[0:15]


// J instruction format
// opcode[26:31] imm[0:25]

void 
mips_inst_interpret(struct mips_regs *reg, struct mmu *m, uint32_t inst)
{
}








