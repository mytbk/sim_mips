#include "syscall.h"
#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void sys_uname(struct mips_regs *r, struct mmu *m)
{
    struct utsname *name = (struct utsname*)mmu_translate_addr(m, CALLARG(r, 0));
    CALLSTATE(r) = 0;
    CALLRET(r) = uname(name);
}

void sys_brk(struct mips_regs *r, struct mmu *m)
{
    fprintf(stderr, "sys_brk: %x\n", CALLARG(r, 0));
    
    CALLRET(r) = mmu_set_brk(m, m->brk+CALLARG(r,0));
    CALLSTATE(r) = 0;
}

void
sys_open(struct mips_regs *r, struct mmu *m)
{
    uint32_t flags = CALLARG(r, 1);
    uint32_t mode = CALLARG(r, 2);
    char *fn = (char*)mmu_translate_addr(m, CALLARG(r, 0));
    CALLRET(r) = open(fn, flags, mode);
    CALLSTATE(r) = 0;
}

static void
sys_setresgid(struct mips_regs *r, struct mmu *m)
{
    fprintf(stderr, "ignore sys_setresgid\n");
    CALLRET(r) = 0;
    CALLSTATE(r) = 0;
}

static void
sys_write(struct mips_regs *r, struct mmu *m)
{
    void *addr = mmu_translate_addr(m, CALLARG(r, 1));
    CALLRET(r) = write(CALLARG(r, 0), addr, CALLARG(r, 2));
    CALLSTATE(r) = 0;
}

static void
sys_writev(struct mips_regs *r, struct mmu *m)
{
    int fd = CALLARG(r, 0);
    const struct iovec *iov =
        (const struct iovec*)mmu_translate_addr(m, CALLARG(r, 1));
    int iovcnt = CALLARG(r, 2);
    CALLRET(r) = writev(fd, iov, iovcnt);
    CALLSTATE(r) = 0;
}

static void
sys_time(struct mips_regs *r, struct mmu *m)
{
    CALLRET(r) = time(CALLARG(r, 0));
    CALLSTATE(r) = 0;
}

static void
sys_clock_gettime(struct mips_regs *r, struct mmu *m)
{
    struct timespec *tp = (struct timespec *)mmu_translate_addr(m, CALLARG(r, 1));
    CALLRET(r) = clock_gettime(CALLARG(r, 0), tp);
    CALLSTATE(r) = 0;
}

void
handle_syscall(struct mips_regs *r, struct mmu *m)
{
    int n;
    fprintf(stderr, "syscall %d pc=0x%x\n", r->regs[2], r->pc);
    
    switch (r->regs[2]) {
    case 4001:
        n = CALLARG(r, 0);
        fprintf(stderr, "program exiting, exit code=%d\n", n);
        exit(n);
    case 4004:
        sys_write(r, m);
        break;
        
    case 4005:
        sys_open(r, m);
        break;
    case 4013:
        sys_time(r, m);
        break;
        
    case 4146:
        sys_writev(r, m);
        break;
        
    case 4045:
        sys_brk(r, m);
        break;
    case 4090:
        sys_setresgid(r, m);
        break;
        
    case 4122: // sys_newuname
        sys_uname(r, m);
        break;
    case 4263:
        sys_clock_gettime(r, m);
        break;
        
    default:
        fprintf(stderr, "syscall %d unhandled\n", r->regs[2]);
        break;
        
    }
}
