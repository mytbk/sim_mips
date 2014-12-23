#include "type.h"
#include "mips.h"
#include "mmu.h"
#include "mipsop.h"
#include "syscall.h"
#include "debugger.h"
#include "simerr.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

extern cache_t sim_icache;
extern cache_t sim_dcache;

static void
exec_delayed_branch(struct mips_regs *r, struct mmu *m)
{
    mips_inst_exec(r, m, *(uint32_t*)mmu_translate_addr(m, r->pc));
    r->pc -= 4;
    return;
}

/* begin R instructions */
DEFUN_R(jr, r, m, rs, rt, rd, shamt)
{
    State.nJump++;
    
    exec_delayed_branch(r, m);
    r->pc = r->regs[rs];
}

DEFUN_R(jalr, r, m, rs, rt, rd, shamt)
{
    State.nJump++;
    
    exec_delayed_branch(r, m);
    r->regs[rd] = r->pc+4;
    r->pc = r->regs[rs];
}

DEFUN_R(syscall, r, m, rs, rt, rd, shamt)
{
    State.nSyscall++;
    
    handle_syscall(r, m);
}

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

DEFUN_R(sllv, r, m, rs, rt, rd, shamt)
{
    r->regs[rd] = r->regs[rt]<<r->regs[rs];
}

DEFUN_R(mult, r, m, rs, rt, rd, shamt)
{
    int s=r->regs[rs], t=r->regs[rt];
    long long result;
    result = s*t;
    r->lo = *(int*)&result;
    r->hi = *(((int*)&result)+1);
}

DEFUN_R(mips_div, r, m, rs, rt, rd, shamt)
{
    int s=r->regs[rs], t=r->regs[rt];
    r->hi = s%t;
    r->lo = s/t;
}

DEFUN_R(mfhi, r, m, rs, rt, rd, shamt)
{
    r->regs[rd] = r->hi;
}

DEFUN_R(mflo, r, m, rs, rt, rd, shamt)
{
    r->regs[rd] = r->lo;
}

DEFUN_R(mthi, r, m, rs, rt, rd, shamt)
{
    r->hi = r->regs[rs];
}

DEFUN_R(mtlo, r, m, rs, rt, rd, shamt)
{
    r->lo = r->regs[rs];
}

r_inst_tab mips_r_insts[64] =
{
    [MR_SLLV] { sllv, "sllv $%d, $%d, $%d" },    
    [MR_JR] { jr, "jr $%d" },
    [MR_JALR] { jalr, "jalr $%d, $%d" },
    [MR_SYSCALL] { syscall, "syscall" },
    [MR_MFHI] { mfhi, "mfhi $%d" },
    [MR_MTHI] { mthi, "mthi $%d" },
    [MR_MFLO] { mflo, "mflo $%d" },
    [MR_MTLO] { mtlo, "mtlo $%d" },
    [MR_MULT] { mult, "mult $%d, $%d" },
    [MR_DIV] { mips_div, "div $%d, $%d" },
    
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

/* begin I instructions */

DEFUN_I(bgez, r, m, rs, rt, imm)
{
    State.nBranch++;
    
    int sgnrs = r->regs[rs];
    
    switch (rt) {
    case 0:
        // bltz 
        if (sgnrs<0) {
            exec_delayed_branch(r, m);
            r->pc += SIGNEXT(imm)*4;
        }
        break;
    case 1:
        // bgez
        if (sgnrs>=0) {
            exec_delayed_branch(r, m);
            r->pc += SIGNEXT(imm)*4;
        }
        break;
    case 0x10:
        // bltzal
        if (sgnrs<0) {
            exec_delayed_branch(r, m);
            r->regs[31] = r->pc+4;
            r->pc += SIGNEXT(imm)*4;
        }
        break;
    case 0x11:
        // bgezal
        if (sgnrs>=0) {
            exec_delayed_branch(r, m);
            r->regs[31] = r->pc+4;
            r->pc += SIGNEXT(imm)*4;
        }
        break;
    default:
        log_msg("error: opcode=1, rt=%d\n", rt);
    }
}


DEFUN_I(beq, r, m, rs, rt, imm)
{
    State.nBranch++;
    
    if (r->regs[rs]==r->regs[rt]) {
        exec_delayed_branch(r, m);
        r->pc += SIGNEXT(imm)*4;
    }
}

DEFUN_I(bne, r, m, rs, rt, imm)
{
    State.nBranch++;
    
    if (r->regs[rs]!=r->regs[rt]) {
        exec_delayed_branch(r, m);
        r->pc += SIGNEXT(imm)*4;
    }
}

DEFUN_I(blez, r, m, rs, rt, imm)
{
    State.nBranch++;
    
    int t=r->regs[rs];
    if (t<=0) {
        exec_delayed_branch(r, m);
        r->pc += SIGNEXT(imm)*4;
    }
}

DEFUN_I(bgtz, r, m, rs, rt, imm)
{
    State.nBranch++;
    
    int t=r->regs[rs];
    if (t>0) {
        exec_delayed_branch(r, m);
        r->pc += SIGNEXT(imm)*4;
    }
}

DEFUN_I(addi, r, m, rs, rt, imm)
{
    r->regs[rt] = r->regs[rs] + SIGNEXT(imm);
}

DEFUN_I(addiu, r, m, rs, rt, imm)
{
    r->regs[rt] = r->regs[rs] + SIGNEXT(imm);
}

DEFUN_I(slti, r, m, rs, rt, imm)
{
    int t1 = r->regs[rs], t2 = SIGNEXT(imm);
    r->regs[rt] = (t1<t2);
}

DEFUN_I(sltiu, r, m, rs, rt, imm)
{
    uint32_t t1 = r->regs[rs], t2 = imm;
    r->regs[rt] = (t1<t2);
}

DEFUN_I(andi, r, m, rs, rt, imm)
{
    uint32_t t1 = imm;
    r->regs[rt] = r->regs[rs] & t1;
}

DEFUN_I(ori, r, m, rs, rt, imm)
{
    uint32_t t1 = imm;
    r->regs[rt] = r->regs[rs] | t1;
}

DEFUN_I(xori, r, m, rs, rt, imm)
{
    uint32_t t1 = imm;
    r->regs[rt] = r->regs[rs] ^ t1;
}

DEFUN_I(lb, r, m, rs, rt, imm)
{
    State.nLoad++;

    uint32_t va = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, va);
        
    char *addr = (char*)mmu_translate_addr(m, va);
    if (addr==NULL) {
        log_msg("error: lb: target address %x not exist, pc=%x\n", va, r->pc);
        exit(1);
    } else {
        r->regs[rt] = *addr;
    }
}

DEFUN_I(lui, r, m, rs, rt, imm)
{
    if (rs!=0) {
        log_msg("error: lui instruction, rs!=0\n");
        exit(1);
    }
    r->regs[rt] = imm<<16;
}

DEFUN_I(lw, r, m, rs, rt, imm)
{
    State.nLoad++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    uint32_t* my_addr = (uint32_t*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: lw: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        r->regs[rt] = *my_addr;
    }
}

DEFUN_I(lbu, r, m, rs, rt, imm)
{
    State.nLoad++;

    uint32_t va = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, va);
    
    unsigned char *addr = (unsigned char*)mmu_translate_addr(m, va);
    if (addr==NULL) {
        log_msg("error: lbu: target address %x not exist, pc=%x\n", va, r->pc);
        exit(1);
    } else {
        r->regs[rt] = *addr;
    }
}

DEFUN_I(lhu, r, m, rs, rt, imm)
{
    State.nLoad++;

    uint32_t va = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, va);
    
    uint16_t *addr = (uint16_t*)mmu_translate_addr(m, va);
    if (addr==NULL) {
        log_msg("error: lhu: target address %x not exist, pc=%x\n", va, r->pc);
        exit(1);
    } else {
        r->regs[rt] = *addr;
    }
}

DEFUN_I(sb, r, m, rs, rt, imm)
{
    State.nStore++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    char *my_addr = (char*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: sb: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        *my_addr = r->regs[rt];
    }
}

DEFUN_I(sh, r, m, rs, rt, imm)
{
    State.nStore++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    uint16_t *my_addr = (uint16_t*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: sh: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        *my_addr = r->regs[rt];
    }
}

DEFUN_I(swl, r, m, rs, rt, imm)
{
    State.nStore++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    uint16_t *my_addr = (uint16_t*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: swl: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        *my_addr = r->regs[rt]>>16;
    }
}

DEFUN_I(sw, r, m, rs, rt, imm)
{
    State.nStore++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    uint32_t* my_addr = (uint32_t*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: sw: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        *my_addr = r->regs[rt];
    }
}

DEFUN_I(swr, r, m, rs, rt, imm)
{
    State.nStore++;
    
    uint32_t addr = r->regs[rs]+SIGNEXT(imm);
    cache_access(&sim_dcache, addr);
    
    uint16_t *my_addr = (uint16_t*)mmu_translate_addr(m, addr);
    if (my_addr==NULL) {
        log_msg("error: swl: target address %x not exist, pc=%x\n", addr, r->pc);
        exit(1);
    } else {
        *my_addr = r->regs[rt];
    }
}

i_inst_tab mips_i_insts[64] =
{
    [MI_BGEZ] { bgez, "bgez/bltz(al) $%d, %d, %x" },
    [MI_BEQ] { beq, "beq $%d, $%d, %x" },
    [MI_BNE] { bne, "bne $%d, $%d, %x" },
    [MI_BLEZ] { blez, "blez $%d, $%d" },
    [MI_BGTZ] { bgtz, "bgtz $%d, $d" },
    
    [MI_ADDI] { addi, "addi $%d, $%d, %d" },
    [MI_ADDIU] { addiu, "addiu $%d, $%d, %d" },
    [MI_SLTI] { slti, "slti $%d, $%d, %d" },
    
    [MI_SLTIU] { sltiu, "sltiu $%d, $%d, %d" },
    
    [MI_ANDI] { andi, "andi $%d, $%d, %x" },
    [MI_ORI] { ori, "ori $%d, $%d, %x" },
    [MI_XORI] { xori, "xori $%d, $%d, %x" },
    [MI_LUI] { lui, "lui $%d, %x" },
    [MI_LB] { lb, "lb $%d, %d($%d)" },
    [MI_LW] { lw, "lw $%d, %d($%d)" },
    [MI_LBU] { lbu, "lbu $%d, %d($%d)" },
    [MI_LHU] { lhu, "lhu $%d, %d($%d)" },
    
    [MI_SB] { sb, "sb $%d, %d($%d)" },
    [MI_SH] { sh, "sh $%d, %d($%d)" },
    [MI_SWL] { swl, "swl $%d, %d($%d)" },    
    [MI_SW] { sw, "sw $%d, %d($%d)" },
    [MI_SWR] { swr, "swr $%d, %d($%d)" }
    
};

/* begin J instructions */
DEFUN_J(j, r, m, imm)
{
    State.nJump++;
    
    exec_delayed_branch(r, m);
    
    imm <<= 2;
    r->pc &= 0xf0000000;
    r->pc |= imm;
}

DEFUN_J(jal, r, m, imm)
{
    State.nJump++;
    
    exec_delayed_branch(r, m);
    
    r->regs[31] = r->pc+4;
    imm <<= 2;
    r->pc &= 0xf0000000;
    r->pc |= imm;
}

j_inst_tab mips_j_insts[64] = 
{
    [MJ_J] { j, "j %x" },
    [MJ_JAL] { jal, "j %x" }    
};
    
// R instruction format
// opcode[26:31]=0 rs[21:25] rt[16:20] rd[11:15] shamt[6:10] funct[0:5]
void
r_inst(struct mips_regs *reg, struct mmu *m, int rs, int rt, int rd,
       int shamt, int funct)
{
    if (mips_r_insts[funct].exec_r_inst) {
        mips_r_insts[funct].exec_r_inst(reg, m, rs, rt, rd, shamt);
    } else {
        log_msg("unknown R-instruction, funct=%d pc=%x\n", funct, reg->pc);
        exit(1);
    }
}

// I instruction format
// opcode[26:31] rs[21:25] rt[16:20] imm[0:15]
void i_inst(struct mips_regs *reg, struct mmu *m, int opcode, int rs, int rt, int imm)
{
    if (mips_i_insts[opcode].exec_i_inst) {
        mips_i_insts[opcode].exec_i_inst(reg, m, rs, rt, imm);
    } else {
        log_msg("unknown I-instruction, opcode=%d pc=%x\n", opcode, reg->pc);
        exit(1);
    }
}

// J instruction format
// opcode[26:31] imm[0:25]
void j_inst(struct mips_regs *reg, struct mmu *m, int opcode, int imm)
{
    if (mips_j_insts[opcode].exec_j_inst) {
        mips_j_insts[opcode].exec_j_inst(reg, m, imm);
    } else {
        log_msg("unknown J-instruction, opcode=%d pc=%x\n", opcode, reg->pc);
        exit(1);
    }
}

void 
mips_inst_exec(struct mips_regs *reg, struct mmu *m, uint32_t inst)
{
    mipsinst_t mi;
    extern int inst_count;

    cache_access(&sim_icache, reg->pc);
    
    mi.bytes = inst;
    reg->pc += 4;
    inst_count++;

    switch (get_inst_type(mi)) {
    case R_TYPE:
        State.r_inst++;
        r_inst(reg, m, mi.r.rs, mi.r.rt, mi.r.rd, mi.r.sa, mi.r.funct);
        break;
    case I_TYPE:
        State.i_inst++;
        i_inst(reg, m, mi.i.opcode, mi.i.rs, mi.i.rt, mi.i.imm);
        break;
    case J_TYPE:
        State.j_inst++;
        j_inst(reg, m, mi.j.opcode, mi.j.imm);
        break;
        
    default:
        log_msg("error: instruction %x cannot be executed.\n", inst);
        exit(1);
    }
}

static void statechk(struct mips_regs *r)
{
    if (r->regs[0]!=0) {
        log_msg("warning: pc=%x $0!=0, setting $0=0\n", r->pc);
        r->regs[0] = 0;
    }
}

void
mips_run(struct mips_regs *r, struct mmu *m, uint32_t entry_addr, int debug)
{
    mmu_alloc_heap_stack(m, r);
    
    r->pc = entry_addr;

    if (debug) {
        int ret = 1;
        while (ret) {
            ret = debugger(r, m);
        }
    }
            
    while (1) {
        statechk(r);
        uint32_t inst = *(uint32_t*)mmu_translate_addr(m, r->pc);
        mips_inst_exec(r, m, inst);
    }
}

