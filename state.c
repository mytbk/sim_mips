#include <stdio.h>
#include "simerr.h"
#include "state.h"
#include "cache.h"

state_t State = {};

void
state_print()
{
    unsigned nInst = State.r_inst+State.i_inst+State.j_inst;
    
    log_msg("### Instructions ###\n");
    log_msg("R-type:  %d (%lf%%)\n", State.r_inst, 100.0*State.r_inst/nInst);
    log_msg("I-type:  %d (%lf%%)\n", State.i_inst, 100.0*State.i_inst/nInst);
    log_msg("J-type:  %d (%lf%%)\n", State.j_inst, 100.0*State.j_inst/nInst);
    log_msg("Load:    %d (%lf%%)\n", State.nLoad, 100.0*State.nLoad/nInst);
    log_msg("Store:   %d (%lf%%)\n", State.nStore, 100.0*State.nStore/nInst);
    log_msg("Jump:    %d (%lf%%)\n", State.nJump, 100.0*State.nJump/nInst);
    log_msg("Branch:  %d (%lf%%)\n", State.nBranch, 100.0*State.nBranch/nInst);
    log_msg("Syscall: %d (%lf%%)\n", State.nSyscall, 100.0*State.nSyscall/nInst);
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



















