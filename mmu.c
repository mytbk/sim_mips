#include "type.h"
#include "mmu.h"
#include "mips.h"
#include <stdlib.h>

int 
mmu_init(struct mmu *m)
{
    m->mmuhdr = (struct Block*)calloc(sizeof(struct Block), 1);
    return 0;
}

void*
mmu_alloc(struct mmu *m, uint32_t vma, uint32_t memsz)
{
    struct Block *p = m->mmuhdr;
    while (p->next!=NULL) {
        p = p->next;
    }
    // append a block
    p->next = (struct Block*)malloc(sizeof(struct Block));
    p->next->pa_start = malloc(memsz);
    p->next->va_start = vma;
    p->next->size = memsz;
    p->next->next = NULL;

    // return the physical address allocated
    return p->next->pa_start;
}

void*
mmu_translate_addr(struct mmu *m, uint32_t vm)
{
    struct Block *p = m->mmuhdr;
    while (p!=NULL
           && !(p->va_start<=vm && p->va_start+p->size>vm)){
        p = p->next;
    }
    if (p==NULL) {
        return NULL;
    } else {
        return p->pa_start+(vm-p->va_start);
    }
}

void
mmu_alloc_heap_stack(struct mmu *m, struct mips_regs *r)
{
    // allocate stack at 0xf0000000 to 0xf0000000+8M
    mmu_alloc(m, 0xf0000000, 1<<23);
    r->regs[29] = 0xf0000000+(1<<23);
    m->nextfree = 0xf0000000;
}

uint32_t
mmu_heap_alloc(struct mmu *m, uint32_t size)
{
    uint32_t ret = m->nextfree;
    m->nextfree += size;
    // align to 4 bytes
    m->nextfree = (m->nextfree+3)&~3;
    return ret;
}
