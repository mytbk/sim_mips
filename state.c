#include <stdio.h>
#include "simerr.h"
#include "state.h"
#include "cache.h"

state_t State = {};

void
state_print()
{
    log_msg("### Instructions ###\n");
    log_msg("R-type:  %d\n", State.r_inst);
    log_msg("I-type:  %d\n", State.i_inst);
    log_msg("J-type:  %d\n", State.j_inst);
    log_msg("Load:    %d\n", State.nLoad);
    log_msg("Store:   %d\n", State.nStore);
    log_msg("Jump:    %d\n", State.nJump);
    log_msg("Branch:  %d\n", State.nBranch);
    log_msg("Syscall: %d\n", State.nSyscall);
    log_msg("\n### Cache ###\n");
    log_msg("D-Cache hit:  %d\n", sim_dcache.nHit);
    log_msg("D-Cache miss: %d\n", sim_dcache.nMiss);
    log_msg("D-Cache hit ratio: %lf\n",
            (double)sim_dcache.nHit/(sim_dcache.nHit+sim_dcache.nMiss));
    log_msg("I-Cache hit:  %d\n", sim_icache.nHit);
    log_msg("I-Cache miss: %d\n", sim_icache.nMiss);
    log_msg("I-Cache hit ratio: %lf\n", (double)sim_icache.nHit/(sim_icache.nHit+sim_icache.nMiss));
    log_msg("Cycles: %d\n", sim_icache.nHit+(sim_icache.nMiss+sim_dcache.nMiss)*missTime);
}



















