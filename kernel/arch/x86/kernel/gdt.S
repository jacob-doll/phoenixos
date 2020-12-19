.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
    mov 4(%esp), %eax
    lgdt (%eax)
    jmp $0x08, $._load_gdt

._load_gdt:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov $0x28, %ax
    ltr %ax
    ret
