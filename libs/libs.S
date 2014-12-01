.globl write
write:  addi $v0, $0, 4004
        syscall
        jr $ra
        nop
        
