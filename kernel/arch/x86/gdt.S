.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
    mov 4(%esp), %eax
    lgdt (%eax)
    
    mov $0x28, %ax
    ltr %ax
    ret
