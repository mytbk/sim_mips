        .globl write
write:  addi $v0, $0, 4004
        syscall
        jr $ra
        nop
        
        .globl exit
exit:   addi $v0, $0, 4001
        syscall
        
