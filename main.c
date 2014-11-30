#include <stdio.h>
#include <stdlib.h>
#include <linux/elf.h>
#include "mmu.h"
#include "mipsop.h"
void print_disas_string(mipsinst_t);

struct mmu sim_mmu;
struct mips_regs reg;
int inst_count=0;

void sim_exit()
{
    int i;
    
    fprintf(stderr, "%d instructions executed\n", inst_count);
    for (i=0; i<32; i++) {
        fprintf(stderr, "reg[%d]=%08x ", i, reg.regs[i]);
        if (i%4==3) {
            fprintf(stderr, "\n");
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    struct elf32_hdr hdr;
    struct elf32_phdr phdr;
    
    int i, dbg=0;
    atexit(sim_exit);
    
    fp = fopen(argv[1], "rb");
    fread(&hdr, sizeof(hdr), 1, fp);
    printf("entry point: %p\n", hdr.e_entry);
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
        
        fprintf(stderr, "Loaded segment type: %d\n", phdr.p_type);
    }
    
    uint32_t *entry_addr = (uint32_t*)mmu_translate_addr(&sim_mmu, hdr.e_entry);
    fprintf(stderr, "The first instruction word: %p\n", *entry_addr);
    print_disas_string(*(mipsinst_t*)entry_addr);

    if (argc>=3 && strcmp(argv[2], "-d")==0) {
        dbg = 1;
    }
    
    mips_run(&reg, &sim_mmu, hdr.e_entry, dbg);
    
    fclose(fp);

    return 0;
}



















