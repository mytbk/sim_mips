#include "type.h"
#include "mmu.h"
#include "mips.h"
#include <stdlib.h>

int 
mmu_init(struct mmu *m)
{
    m->pgdir = calloc(1024, sizeof(void**));
    return 0;
}

static void
set_pg_map(struct mmu *m, uint32_t va, void* addr)
{
    size_t pdx=PDX(va), ptx=PTX(va);
        
    if (m->pgdir[pdx]==NULL) {
        m->pgdir[pdx] = calloc(1024, sizeof(void*));
    }
    m->pgdir[pdx][ptx] = addr;
}

void*
mmu_alloc(struct mmu *m, uint32_t vma, uint32_t memsz)
{
    uint32_t start = ROUNDDOWN(vma, PGSIZE);
    uint32_t end = ROUNDUP(vma+memsz, PGSIZE);
    void *addr = malloc(end-start);
    void *base = addr;
    
    while (start<end) {
        set_pg_map(m, start, addr);
        start += PGSIZE;
        addr += PGSIZE;
    }
    return base+PGOFF(vma);
}

void*
mmu_translate_addr(struct mmu *m, uint32_t vm)
{
    size_t pdx=PDX(vm), ptx=PTX(vm);
    if (m->pgdir[pdx]==NULL) {
        return NULL;
    }
    return m->pgdir[pdx][ptx]+PGOFF(vm);
}

uint32_t
mmu_set_brk(struct mmu *m, uint32_t vm)
{
    m->brk = vm;
    return m->brk;
}

void
mmu_alloc_heap_stack(struct mmu *m, struct mips_regs *r)
{
    // allocate a user stack
    // and also some free space for kernel data
    mmu_alloc(m, USTKTOP-USTKSIZE, USTKSIZE*2);
    r->regs[29] = USTKTOP-16;
    // the words on the stack is
    // argc
    // argv[0],...,argv[argc-1]
    // NULL
    // envp[0],...,NULL
    uint32_t *sp = (uint32_t*)mmu_translate_addr(m, r->regs[29]);
    uint32_t _argv0 = mmu_heap_alloc(m, 9);
    char* argv0 = (char*)mmu_translate_addr(m, _argv0);
    strcpy(argv0, "mipsprog");
    
    sp[0] = 1;
    sp[1] = _argv0;
    
    m->nextfree = USTKTOP;
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








