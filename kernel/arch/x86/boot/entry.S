.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp

    /*
    GDT
    Paging
    Global constructors
    */

    .extern arch_main
    push %eax
    call arch_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
