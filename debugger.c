#include "mips.h"

void
print_regs(struct mips_regs *r)
{
    for (i=0; i<32; i++) {
        fprintf(stderr, "reg[%d]=%08x ", i, r->regs[i]);
        if (i%4==3) {
            fprintf(stderr, "\n");
        }
    }
}
