/** MIPS instruction parser */

#include "mipsop.h"
#include <stdio.h>

insttype_t get_inst_type(mipsinst_t inst)
{
    if (inst.i.opcode==0) {
        return R_TYPE;
    }
    else if (inst.i.opcode==2 || inst.i.opcode==3) {
        // j or jal
        return J_TYPE;
    }
    else {
        return I_TYPE;
    }
}

extern r_inst_tab mips_r_insts[];
extern i_inst_tab mips_i_insts[];
extern j_inst_tab mips_j_insts[];

void
print_disas_string(mipsinst_t inst)
{
    switch (get_inst_type(inst)) {
    case R_TYPE:
        if (inst.r.funct==MR_SLL || inst.r.funct==MR_SRL) {
            fprintf(stderr, mips_r_insts[inst.r.funct].asmstr,
                    inst.r.rd, inst.r.rt, inst.r.sa);
        } else {
            fprintf(stderr, mips_r_insts[inst.r.funct].asmstr,
                    inst.r.rd, inst.r.rs, inst.r.rt);
        }
        break;
    case I_TYPE:
        switch (inst.i.opcode) {
        case MI_SW:
        case MI_SWL:
        case MI_SWR:
        case MI_LW:
        case MI_SB:
        case MI_SH:
        case MI_LB:
        case MI_LBU:
        case MI_LHU:
            fprintf(stderr, mips_i_insts[inst.i.opcode].asmstr,
                    inst.i.rt, inst.i.imm, inst.i.rs);
            break;
            
        default:
            fprintf(stderr, mips_i_insts[inst.i.opcode].asmstr,
                    inst.i.rt, inst.i.rs, inst.i.imm);
            break;
        }
        
    case J_TYPE:
        fprintf(stderr, mips_j_insts[inst.j.opcode].asmstr,
                inst.j.imm);
        break;
        
    default:
        // should not go here
        break;
    }
    fprintf(stderr, "\n");
}





















