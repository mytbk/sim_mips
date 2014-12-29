#ifndef SIM_CACHE_H
#define SIM_CACHE_H

#include "type.h"

typedef struct
{
    unsigned long tag;
    int valid;
    int lastVisit;
}Cache_Block;

typedef struct
{
    int nSetBits, nLines, nBits;
    Cache_Block **cache_block;
    // state
    int nVisits;
    int nHit;
    int nMiss;
}cache_t;

extern cache_t sim_icache;
extern cache_t sim_dcache;

void init_cache(cache_t *cache, int nSets, int nLines, int nBits);
void cache_access(cache_t *cache, uint32_t);

#endif










