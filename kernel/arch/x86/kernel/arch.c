#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/tty.h>

#include "gdt.h"
#include "memory.h"

extern void kernel_main(void);

void arch_main(uintptr_t mem_info) 
{
	terminal_initialize();
	terminal_writestring("Hello, arch World!\n");
	
	mmap_table_t *mem_entries = (mmap_table_t *) mem_info;
	for (uint32_t i = 0; i < mem_entries->size; i++) {
		terminal_writestring("entry\n");
	}	
	
	init_gdt();
	terminal_writestring("GDT initialized!\n");

    kernel_main();
}