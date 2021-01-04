
memory_map:
    mov $0x8104, %di
    xor %ebx, %ebx
    xor %bp, %bp
    mov $0x0534D4150, %edx
    mov $0xe820, %eax
    movl $1, %es:20(%di)
    mov 24, %ecx
    int $0x15
    jc fatal_error
    mov $0x0534D4150, %edx
    cmp %edx, %eax
    jne fatal_error
    test %ebx, %ebx
    je fatal_error
.mmap_loop:
    mov $0xe820, %eax
    movl $1, %es:20(%di)
    mov 24, %ecx
    int $0x15
    jc .mmap_end
    mov $0x0534D4150, %edx
.mmap_begin:
    jcxz .mmap_skip
    cmp $20, %cl
    jbe .mmap_notext
    movl $1, %es:20(%di)
    je .mmap_skip
.mmap_notext:
    mov %es:8(%di), %ecx
    or %es:12(%di), %ecx
    jz .mmap_skip
    inc %bp
    add $24, %di
.mmap_skip:
    test %ebx, %ebx
    jne .mmap_loop
.mmap_end:
    mov %bp, (mmap_buf)
    clc
    ret

.equ mmap_buf, 0x8100
