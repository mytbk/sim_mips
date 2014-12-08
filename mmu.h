#ifndef SIM_MMU_H
#define SIM_MMU_H

#include "type.h"
#include "mips.h"

#define USTKSIZE (1<<13)
#define USTKTOP (0xc0000000)
#define PGSIZE 4096

static inline uint32_t
ROUNDDOWN(x, n)
{
    return x-x%n;
}

static inline uint32_t
ROUNDUP(x, n)
{
    return ROUNDDOWN(x+n-1, n);
}

#define PDX(x) (((x)>>22)&1023)
#define PTX(x) (((x)>>12)&1023)
#define PGOFF(x) ((x)&4095)

struct mmu 
{
    void ***pgdir;
    uint32_t brk;
    /* next free virt address
       that can be allocated in kernel
    */
    uint32_t nextfree;
};

int mmu_init(struct mmu*);
void* mmu_alloc(struct mmu*, uint32_t, uint32_t);
void* mmu_translate_addr(struct mmu*, uint32_t);
void mmu_alloc_heap_stack(struct mmu*, struct mips_regs*);
uint32_t mmu_heap_alloc(struct mmu*, uint32_t);
uint32_t mmu_set_brk(struct mmu*, uint32_t);

#endif    



















