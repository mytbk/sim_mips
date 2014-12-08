        .globl write
write:  addi $v0, $0, 4004
        syscall
        jr $ra
        nop
        
        .globl exit
exit:   addi $v0, $0, 4001
        syscall
        
        .globl open
open:   addi $v0, $0, 4005
        syscall
        jr $ra
        nop
        
        .globl clock_gettime
clock_gettime:
        addi $v0, $0, 4263
        syscall
        jr $ra
        nop
        
