#include <kernel/memory.h>

.section .bss, "aw", @nobits
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .bss, "aw", @nobits
.align 4096
boot_page_directory:
.skip 4096
boot_page_table1:
.skip 4096

.section .text
.global _start
.type _start, @function
_start:
	movl $PHYSICAL_ADDR(boot_page_table1), %edi

	movl $0, %esi
	movl $1023, %ecx

1:
	cmpl $PHYSICAL_ADDR(_kernel_start), %esi
	jl 2f
	cmpl $PHYSICAL_ADDR(_kernel_end), %esi
	jge 3f

	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3:
	movl $(0x000B8000 | 0x003), PHYSICAL_ADDR(boot_page_table1) + 1023 * 4

	movl $(PHYSICAL_ADDR(boot_page_table1) + 0x003), PHYSICAL_ADDR(boot_page_directory) + 0
	movl $(PHYSICAL_ADDR(boot_page_table1) + 0x003), PHYSICAL_ADDR(boot_page_directory) + 768 * 4

	movl $PHYSICAL_ADDR(boot_page_directory), %ecx
	movl %ecx, %cr3

	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	lea 4f, %ecx
	jmp *%ecx

4:
	movl $0, boot_page_directory + 0

	movl %cr3, %ecx
	movl %ecx, %cr3

	mov $stack_top, %esp

    .extern arch_main
    call arch_main

    cli
1:  hlt
    jmp 1b
