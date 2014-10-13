#ifndef SIM_MMU_H
#define SIM_MMU_H

#include "type.h"

struct Block;

struct mmu 
{
    struct Block *mmuhdr;
};

struct Block
{
    uint32_t va_start;
    uint32_t size;
    void *pa_start;
    struct Block *next;
};

int mmu_init(struct mmu*);
void* mmu_alloc(struct mmu*, uint32_t, uint32_t);
void* mmu_translate_addr(struct mmu*, uint32_t);

#endif    



















