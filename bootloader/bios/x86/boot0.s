
.macro print msg
    push %ax
    mov \msg, %si
    call printfunc
    pop %ax
.endm

.equ kernel_offset, 0x1000

/// INIT
.code16
.global init
init:
    
    mov $0x9000, %bp
    mov %bp, %sp

    print $msg_real_mode

    call load_kernel
    call protected

    jmp .

.include "bootloader/bios/x86/print.inc"
.include "bootloader/bios/x86/disk.inc"
.include "bootloader/bios/x86/gdt.inc"

.code16
load_kernel:
    print $msg_load_kernel

    mov $kernel_offset, %bx
    mov $0x10, %dh
    call disk_load
    ret

.code16
protected:
    cli
    lgdt (gdt_descriptor)
    mov %cr0, %eax
    or $0x1, %eax
    mov %eax, %cr0
    jmp $CODE_SEG,$init_pm

.code32
init_pm:
    mov $DATA_SEG, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov $0x90000, %ebp
    mov %ebp, %esp

    call entry

.code32
entry:
    call kernel_offset
    jmp .

/// GLOBALS
msg_real_mode: .ascii "Started in 16-bit Real Mode", "\x0a", "\x0d", "\0"
msg_prot_mode: .ascii "Landed in 32-bit Protected Mode", "\x0a", "\x0d", "\0"
msg_load_kernel: .ascii "Loading kernel into memory", "\x0a", "\x0d", "\0"

.fill 510-(.-init), 1, 0
.word 0xaa55
