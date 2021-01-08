#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/tty.h>
#include <kernel/kprintf.h>
#include <kernel/boot_info.h>
#include <kernel/keyboard.h>

#include "gdt.h"
#include "idt.h"
#include "interrupts.h"
#include "paging.h"
#include "pit.h"

extern void kernel_main(boot_info_table_t *boot_info);

static boot_info_table_t boot_info;

void arch_main(uintptr_t mem_info) 
{
	terminal_initialize();
	kprintf("Hello, arch World!\n");

	boot_info = (boot_info_table_t){
		.num_mmap_entries = *((uint32_t*)mem_info), 
		.mmap_entries = (mmap_entry_t*)(mem_info + 0x0004)
	};

	init_gdt();
	kprintf("GDT initialized!\n");

	init_idt();
	kprintf("IDT initialized!\n");

	map_kernel();
	kprintf("Kernel Mapped\n");

	asm volatile("sti");

    kernel_main(&boot_info);
}