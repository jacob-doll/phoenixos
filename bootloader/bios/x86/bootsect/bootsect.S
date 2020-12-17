#define BIOS_STACK_ADDRESS 0x9000
#define DISK_BUFFER 0x1000
#define NUM_SECTORS_READ 4
#define SECTOR_SIZE 512
#define DISK_BUFFER_SIZE (NUM_SECTORS_READ * SECTOR_SIZE)
#define NUM_COPIES (NUM_SECTORS_READ * 128) // (DISK_BUFFER_SIZE / 4)
#define KERNEL_BUFFER 0x100000

.code16
.global _start
_start:
    ljmp $0, $init

str_entry: .string "Phoenixos Bootloader\n"
str_error: .string "ERROR!\n"

/**
 * init --
 *     
 *     Entry point for BIOS MBR bootloader. Sets up segment
 *     registers and stack. Prints a startup message.
 */
.code16
init:
    cli
    xor %ax, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    mov $BIOS_STACK_ADDRESS, %bp
    mov %bp, %sp

    mov %dl, (disk_drive)

    mov $0x2401, %ax
    int $0x15
    jc fatal_error

    mov $str_entry, %si
    call printfunc

    call memory_map
    call load_kernel
    call enter_protected

    jmp .

.include "bootloader/bios/x86/bootsect/disk.inc"
.include "bootloader/bios/x86/bootsect/gdt.inc"
.include "bootloader/bios/x86/bootsect/memory.inc"

.code16
load_kernel:
    mov $DISK_BUFFER, %bx
    mov $NUM_SECTORS_READ, %dh
    mov (disk_drive), %dl
    call disk_load
    ret

.code16
enter_protected:
    cli
    lgdt (gdt_descriptor)
    mov %cr0, %eax
    or $0x1, %eax
    mov %eax, %cr0
    jmp $CODE_SEG,$init_pm

fatal_error:
    pusha
    push %si
    mov $str_error, %si
    call printfunc
    pop %si
    popa
    cli
    hlt

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

    mov $DISK_BUFFER, %esi
    mov $KERNEL_BUFFER, %edi
    mov $NUM_COPIES, %ecx
    rep movsd

    call entry

.code32
entry:
    mov $mmap_buf, %eax
    call KERNEL_BUFFER
    jmp .

disk_drive: .byte 0x0

.fill 510-(.-_start), 1, 0
.word 0xaa55
