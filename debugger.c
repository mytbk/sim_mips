#include "mips.h"
#include "mmu.h"
#include "mipsop.h"
#include <stdio.h>
#include <string.h>

void print_disas_string(uint32_t inst); // from mipsinst.c

void
print_regs(struct mips_regs *r)
{
    int i;
    
    for (i=0; i<32; i++) {
        fprintf(stderr, "reg[%d]=%08x ", i, r->regs[i]);
        if (i%4==3) {
            fprintf(stderr, "\n");
        }
    }
}

int
debugger(struct mips_regs *r, struct mmu *m)
{
    static char cmd[16];
    char input[16], op[8];
    uint32_t inst;
    uint32_t addr;
        
    printf("> ");
    fgets(input, sizeof(input), stdin);
    if (input[0]!='\n') {
        memcpy(cmd, input, sizeof(input));
    }
    switch (cmd[0]) {
    case 'n':
        inst = *(uint32_t*)mmu_translate_addr(m, r->pc);
        printf("%x: ", r->pc);
        print_disas_string(inst);
        mips_inst_exec(r, m, inst);
        return 1;
    case 'r':
        print_regs(r);
        return 1;
    case 'x':
        sscanf(cmd, "%s%x", op, &addr);
        printf("%x: %x\n", addr, *(uint32_t*)mmu_translate_addr(m, addr));
        return 1;
    case 'c':
        return 0;
    default:
        fprintf(stderr, "unknown debug command.");
        return 1;
    }
}




