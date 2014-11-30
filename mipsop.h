#ifndef SIM_MIPSOP_H
#define SIM_MIPSOP_H
#include "type.h"
#include "mips.h"

#define DEFUN_R(fun,r,m,rs,rt,rd,shamt) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    int rs, int rt, int rd, int shamt)
#define DEFUN_I(fun,r,m,rs,rt,imm) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    int rs, int rt, uint32_t imm)
#define DEFUN_J(fun,r,m,imm) \
    static void fun(struct mips_regs *r, struct mmu *m, \
                    uint32_t imm)

static inline int SIGNEXT(uint32_t x)
{
    signed short xs = x;
    return xs;
}

#define OP3(op,rs,rt,rd) \
    regs->regs[rd] = regs->regs[rs] op regs->regs[rt]

typedef enum {R_TYPE, I_TYPE, J_TYPE} insttype_t;

typedef struct 
{
    unsigned funct:6;
    unsigned sa:5;
    unsigned rd:5;
    unsigned rt:5;
    unsigned rs:5;
    unsigned opcode:6;
} reg_type;

typedef struct
{
    unsigned imm:16;
    unsigned rt:5;
    unsigned rs:5;
    unsigned opcode:6;
} imm_type;

typedef struct
{
    unsigned imm:26;
    unsigned opcode:6;
} jmp_type;

typedef union
{
    unsigned bytes;
    reg_type r;
    imm_type i;
    jmp_type j;
} mipsinst_t;

insttype_t get_inst_type(mipsinst_t);

/* funct for R-format instruction */
enum MIPS_r {
    MR_SLL = 0,
    MR_SRL = 2,
    MR_SRA,
    MR_SLLV,
    MR_SRLV = 6,
    MR_SRAV,
    MR_JR,
    MR_JALR,
    MR_MOVZ,
    MR_MOVN,
    MR_SYSCALL,
    MR_BREAK,
    MR_SYNC = 15,
    MR_MFHI,
    MR_MTHI,
    MR_MFLO,
    MR_MTLO,
    MR_MULT = 24,
    MR_MULTU,
    MR_DIV,
    MR_DIVU,
    MR_ADD = 32,
    MR_ADDU,
    MR_SUB,
    MR_SUBU,
    MR_AND,
    MR_OR,
    MR_XOR,
    MR_NOR,
    MR_SLT = 42,
    MR_SLTU = 43,
    MR_TGE = 48,
    MR_TGEU,
    MR_TLT,
    MR_TLTU,
    MR_TEQ,
    MR_TNE = 54
};

typedef struct
{
    void (*exec_r_inst)(struct mips_regs*, struct mmu*, int, int, int, int);
    char *asmstr;
} r_inst_tab;


/* opcode for I-format and J-format */
enum MIPS_imm {
    MI_BGEZ = 1,
    MJ_J = 2,
    MJ_JAL = 3,
    MI_BEQ,
    MI_BNE,
    MI_BLEZ,
    MI_BGTZ,
    MI_ADDI,
    MI_ADDIU,
    MI_SLTI,
    MI_SLTIU,
    MI_ANDI,
    MI_ORI,
    MI_XORI,
    MI_LUI,
    MI_LB = 32,
    MI_LH,
    MI_LWL,
    MI_LW,
    MI_LBU,
    MI_LHU,
    MI_LWR,
    MI_SB = 40,
    MI_SH,
    MI_SWL,
    MI_SW,
    MI_SWR = 46,
    MI_CACHE,
    MI_LL,
    MI_LWC1,
    MI_LWC2,
    MI_PREF,
    MI_LDC1 = 53,
    MI_LDC2,
    MI_SC = 56,
    MI_SWC1,
    MI_SWC2,
    MI_SDC1 = 61,
    MI_SDC2
};

typedef struct
{
    void (*exec_i_inst)(struct mips_regs*, struct mmu*, int, int, uint32_t);
    char *asmstr;
} i_inst_tab;

typedef struct
{
    void (*exec_j_inst)(struct mips_regs*, struct mmu*, int);
    char *asmstr;
} j_inst_tab;

void mips_run(struct mips_regs*, struct mmu*, uint32_t, int debug);
void mips_inst_exec(struct mips_regs*, struct mmu*, uint32_t);

#endif    
    


















