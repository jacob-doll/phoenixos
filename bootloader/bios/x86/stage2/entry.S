
.extern boot_main

.code32
.section .text
.global _start
_start:
    call boot_main
    jmp .
