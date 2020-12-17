#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/tty.h>

#include "gdt.h"

extern void kernel_main(void);

void arch_main(void) 
{
	terminal_initialize();
	terminal_writestring("Hello, arch World!\n");
	
	init_gdt();
	terminal_writestring("GDT initialized!\n");

    kernel_main();
}