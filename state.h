#ifndef SIM_STATE_H
#define SIM_STATE_H

typedef struct
{
    unsigned r_inst;
    unsigned i_inst;
    unsigned j_inst;
    unsigned nLoad;
    unsigned nStore;
    unsigned nJump;
    unsigned nBranch;
    unsigned nSyscall;
    unsigned cache_hit;
    unsigned cache_miss;
} state_t;

extern state_t State;

void state_print();

#endif










