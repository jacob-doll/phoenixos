#define BIOS_STACK_ADDRESS 0x1000
#define DISK_BUFFER 0x1800

/**
 * 
 */
.code16
.global init
init:
    cli
    xor %ax, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov $BIOS_STACK_ADDRESS, %bp
    mov %bp, %sp

    mov %dl, (disk_drive)

    mov $msg_real_mode, %si
    call printfunc

    call load_kernel
    call protected

    jmp .

.include "bootloader/bios/x86/disk.inc"
.include "bootloader/bios/x86/gdt.inc"

.code16
load_kernel:
    mov $msg_load_kernel, %si
    call printfunc

    mov $DISK_BUFFER, %bx
    mov $0x10, %dh
    mov (disk_drive), %dl
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

printfunc:
    lodsb
    or %al, %al
    jz .end
    mov $0x0e, %ah
    int $0x10
    jmp printfunc
.end:
    ret

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
    call DISK_BUFFER
    jmp .

/// GLOBALS
msg_real_mode: .string "Started in 16-bit Real Mode"
msg_load_kernel: .string "Loading kernel into memory"

disk_drive: .byte 0x0

.fill 510-(.-init), 1, 0
.word 0xaa55
