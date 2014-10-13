#include <stdio.h>
#include <stdlib.h>
#include <linux/elf.h>
#include "mmu.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    struct elf32_hdr hdr;
    struct elf32_phdr phdr;
    struct mmu sim_mmu;
    
    int i;
        
    fp = fopen(argv[1], "rb");
    fread(&hdr, sizeof(hdr), 1, fp);
    printf("entry point: %p\n", hdr.e_entry);
    fseek(fp, hdr.e_phoff, SEEK_SET);
    
    mmu_init(&sim_mmu);
    
    for (i=0; i<hdr.e_phnum; i++){
        // read a program header
        fread(&phdr, sizeof(phdr), 1, fp);
        
        void* ph_ad = mmu_alloc(&sim_mmu, phdr.p_vaddr, phdr.p_memsz);
        long pos = ftell(fp);
        fseek(fp, phdr.p_offset, SEEK_SET);
        fread(ph_ad, phdr.p_filesz, 1, fp);
        fseek(fp, pos, SEEK_SET);
    }
    
    fclose(fp);
    return 0;
}



















