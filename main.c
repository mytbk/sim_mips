#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/elf.h>
#include "mmu.h"
#include "mipsop.h"
#include "simerr.h"
#include "state.h"
#include "cache.h"

void print_disas_string(mipsinst_t);

struct mmu sim_mmu;
struct mips_regs reg;

int inst_count=0;

static void
helpmsg(const char* str)
{
    printf("%s [options] <prog> [args]\n", str);
    puts("Options:");
    puts(" -d: debug mode");
    puts(" -c <set> <line> <bit>: set cache sets, associativity, and block size");
    puts(" -t <tracefile>: set trace file");
    puts(" -l <logfile>: set log file");
    exit(1);
}

void sim_exit()
{
    int i;
    
    log_msg("%d instructions executed\n", inst_count);
    for (i=0; i<32; i++) {
        log_msg("reg[%d]=%08x ", i, reg.regs[i]);
        if (i%4==3) {
            log_msg("\n");
        }
    }
    state_print();
    log_end();
}

int main(int argc, char *argv[])
{
    FILE *fp;
    struct elf32_hdr hdr;
    struct elf32_phdr phdr;
    
    int i, dbg=0;

    char *logfile = "sim.log";
    char *tracefile = NULL;
    
    // cache
    int nSets=1024, nLines=4, nBits=2;
    
    for (i=1; i<argc; i++) {
        if (strcmp(argv[i], "-d")==0) {
            dbg = 1;
            continue;
        }
        if (strcmp(argv[i], "-c")==0) {
            if (i+3<argc) {
                nSets = atoi(argv[i+1]);
                nLines = atoi(argv[i+2]);
                nBits = atoi(argv[i+3]);
            } else {
                helpmsg(argv[0]);
            }
            i+=3;
            continue;
        }
        if (strcmp(argv[i], "-l")==0) {
            if (i+1<argc) {
                logfile = argv[i+1];
            } else {
                helpmsg(argv[0]);
            }
            i++;
            continue;
        }
        if (strcmp(argv[i], "-t")==0) {
            if (i+1<argc) {
                tracefile = argv[i+1];
            } else {
                helpmsg(argv[0]);
            }
            i++;
            continue;
        }
                    
        break;
    }

    if (i>=argc) {
        helpmsg(argv[0]);
    }
    
    log_init(logfile);
    if (tracefile) {
        trace_init(tracefile);
    }
    
    atexit(sim_exit);
            
    fp = fopen(argv[i], "rb");
    fread(&hdr, sizeof(hdr), 1, fp);
    log_msg("entry point: %x\n", hdr.e_entry);
    fseek(fp, hdr.e_phoff, SEEK_SET);
    
    mmu_init(&sim_mmu);
    
    for (i=0; i<hdr.e_phnum; i++){
        // read a program header
        fread(&phdr, sizeof(phdr), 1, fp);
        if (!(phdr.p_type==PT_LOAD)) {
            continue;
        }
        
        void* ph_ad = mmu_alloc(&sim_mmu, phdr.p_vaddr, phdr.p_memsz);
        long pos = ftell(fp);
        fseek(fp, phdr.p_offset, SEEK_SET);
        fread(ph_ad, phdr.p_filesz, 1, fp);
        fseek(fp, pos, SEEK_SET);
        mmu_set_brk(&sim_mmu, phdr.p_vaddr+phdr.p_memsz);
        
        log_msg("Loaded segment type: %d\n", phdr.p_type);
    }
    
    uint32_t *entry_addr = (uint32_t*)mmu_translate_addr(&sim_mmu, hdr.e_entry);
    log_msg("The first instruction word: %x\n", *entry_addr);

    if (argc>=3 && strcmp(argv[2], "-d")==0) {
        dbg = 1;
    }

    log_msg("cache: set=%d line=%d bit=%d\n", nSets, nLines, nBits);
    
    init_cache(&sim_icache, nSets, nLines, nBits);
    init_cache(&sim_dcache, nSets, nLines, nBits);
    
    mips_run(&reg, &sim_mmu, hdr.e_entry, dbg);
    
    fclose(fp);

    return 0;
}











