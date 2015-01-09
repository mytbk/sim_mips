#include "cache.h"
#include "simerr.h"
#include <stdlib.h>

cache_t sim_icache;
cache_t sim_dcache;

void
init_cache(cache_t *cache, int s, int l, int b)
{
    int i;

    cache->nSetBits = 0;
    for (i=1; i<s; i<<=1) {
        cache->nSetBits++;
    }
    
    cache->nLines = l;
    cache->nBits = b;
    cache->cache_block = (Cache_Block**)malloc(sizeof(Cache_Block*)*s);
    for (i=0; i<s; i++) {
        cache->cache_block[i] = (Cache_Block*)calloc(sizeof(Cache_Block), l);
    }
    cache->nHit = cache->nMiss = cache->nVisits = 0;
}

void
cache_access(cache_t *cache, uint32_t addr)
{
    int i, idx;
    
    int set = (addr>>cache->nBits)&((1<<cache->nSetBits)-1);
    unsigned long tag = addr>>(cache->nBits+cache->nSetBits);
    cache->nVisits++;
    
    for (i=0; i<cache->nLines; i++) {
        Cache_Block *b = &cache->cache_block[set][i];
        if (b->valid && b->tag==tag) {
            if (cache==&sim_dcache) {
                trace_msg("%x HIT\n", addr);
            }
            cache->nHit++;
            b->lastVisit = cache->nVisits;
            return;
        } 
    }
    // cache miss
    if (cache==&sim_dcache) {
        trace_msg("%x MISS\n", addr);
    }
    
    cache->nMiss++;
    for (i=0; i<cache->nLines; i++) {
        Cache_Block *b = &cache->cache_block[set][i];
        if (!b->valid) {
            // have place
            b->valid = 1;
            b->tag = tag;
            b->lastVisit = cache->nVisits;
            return;
        }
    }
    // need to evict one cache line
    idx = 0;
    for (i=1; i<cache->nLines; i++) {
        Cache_Block *b = &cache->cache_block[set][i];
        if (b->lastVisit<cache->cache_block[set][idx].lastVisit) {
            idx = i;
        }
    }
    Cache_Block *b = &cache->cache_block[set][idx];
    b->tag = tag;
    b->lastVisit = cache->nVisits;
}
















