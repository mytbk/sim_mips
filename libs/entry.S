        .globl __start
__start:
        jal main
        nop
        add $a0, $0, $v0
        addi $v0, $0, 4001        
        syscall

