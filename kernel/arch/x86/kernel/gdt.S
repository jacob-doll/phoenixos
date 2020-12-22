#include <kernel/memory.h>

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $0x10, %eax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    mov $0x28, %ax
    ltr %ax
    ret
