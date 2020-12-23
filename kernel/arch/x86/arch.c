#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/tty.h>
#include <kernel/kprintf.h>
#include <kernel/memory.h>

#include "gdt.h"
#include "paging.h"

extern void kernel_main(void);

void arch_main(uintptr_t mem_info) 
{
	terminal_initialize();
	kprintf("Hello, arch World!\n");
	uint32_t size = *((uint32_t*)mem_info);
	mem_info += 0x0004;
	while (size > 0) {
		mmap_entry_t entry = (*((mmap_entry_t*)mem_info));
		kprintf("base: %x%x ", entry.base_hi, entry.base_lo);
		kprintf("length: %x%x ", entry.length_hi, entry.length_lo);
		kprintf("type: %u\n", entry.type);
		--size;
		mem_info += sizeof(mmap_entry_t);
	}

	init_gdt();
	kprintf("GDT initialized!\n");

	map_kernel();

    kernel_main();
}