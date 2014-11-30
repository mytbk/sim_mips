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

void print_disas_string(mipsinst_t inst)
{
    switch (get_inst_type(inst)) {
    case R_TYPE:
        if (inst.r.funct==MR_SLL || inst.r.funct==MR_SRL) {
            printf(mips_r_insts[inst.r.funct].asmstr,
                   inst.r.rd, inst.r.rt, inst.r.sa);
        } else {
            printf(mips_r_insts[inst.r.funct].asmstr,
                   inst.r.rd, inst.r.rs, inst.r.rt);
        }
        break;
    case I_TYPE:
        printf(mips_i_insts[inst.i.opcode].asmstr,
               inst.i.rs, inst.i.rt, inst.i.imm);
        break;
        
    case J_TYPE:
        
    default:
        // should not go here
        break;
    }
    puts("");
}





















