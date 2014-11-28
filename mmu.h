#ifndef SIM_MMU_H
#define SIM_MMU_H

#include "type.h"
#include "mips.h"

#define USTKSIZE (1<<13)
#define USTKTOP (0xc0000000)

struct Block;

struct mmu 
{
    struct Block *mmuhdr;
    uint32_t brk;
    /* next free virt address
       that can be allocated in kernel
    */
    uint32_t nextfree;
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
void mmu_alloc_heap_stack(struct mmu*, struct mips_regs*);
uint32_t mmu_heap_alloc(struct mmu*, uint32_t);
uint32_t mmu_set_brk(struct mmu*, uint32_t);

#endif    



















