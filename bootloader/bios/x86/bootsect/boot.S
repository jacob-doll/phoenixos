
#define DAP_struct 0x5000
#define mmap_size 0x5100
#define mmap_buf 0x5104
#define stage2_entry 0x7E00

.code16
.global _start
_start:
    cli
    ljmp $0, $init

init:
    xor %ax, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov 0x9000, %sp
    sti

    mov %dl, (disk_drive)


    mov (disk_drive), %dl
    mov $stage2_entry, %bx
    mov (stage2_size), %ecx
    call disk_load

    call memory_map

    cli
    lgdt (gdt_descriptor)
    mov %cr0, %eax
    or $0x1, %eax
    mov %eax, %cr0
    jmp $0x8, $init_pm

fatal_error:
    cli
1:  hlt
    jmp 1b

.code32
init_pm:
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov $0x90000, %ebp
    mov %ebp, %esp

    call stage2_entry

/**
 *  IN:
 *  DL = drive
 *  ES = buffer segment
 *  BX = buffer offset
 *  ECX = bytes to load
 */
.code16
disk_load:
    pusha

    mov $DAP_struct, %si

    movw $0x10,         (%si)   // size of DAP (16 bytes)
    movw $0x01,        2(%si)   // number of sectors to read
    movw %bx,          4(%si)   // offset
    movw %es,          6(%si)   // segment    
    movl $0x00000001,  8(%si)   // start sector
    movl $0x00000000, 12(%si)   // (cont. )
    
    push %dx
    push %ebx

    mov %cx, %ax
    shr $16, %ecx
    mov %cx, %dx
    xor %cx, %cx
    mov $512, %ebx
    div %ebx
    test %dx, %dx
    setnz %cl
    add %ax, %cx

    pop %ebx
    pop %dx

1:
    mov $0x42, %ah
    int $0x13
    jc fatal_error

    addw $512, 4(%si)
    incw 8(%si)
    adcw $0, 12(%si)

    loop 1b

    popa
    ret

memory_map:
    mov $mmap_buf, %di
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
    mov %bp, (mmap_size)
    clc
    ret

// GLOBALS
disk_drive: .byte 0x0
gdt_start: 
    .long 0x0
    .long 0x0
gdt_code: 
    .word 0xffff    
    .word 0x0       
    .byte 0x0       
    .byte 0b10011010
    .byte 0b11001111
    .byte 0x0
gdt_data: 
    .word 0xffff    
    .word 0x0       
    .byte 0x0       
    .byte 0b10010010
    .byte 0b11001111
    .byte 0x0
gdt_end:
gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long gdt_start

// Stage two data
.fill 0x1AC-(.-_start), 1, 0
stage2_size: .long 0

.fill 510-(.-_start), 1, 0
.word 0xaa55
