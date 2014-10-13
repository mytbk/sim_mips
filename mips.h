#ifndef SIM_MIPS_H
#define SIM_MIPS_H

#include "type.h"

struct mips_regs
{
    uint32_t regs[32];
    uint32_t hi, lo;
};

#endif
