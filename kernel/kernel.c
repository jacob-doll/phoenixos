#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/kprintf.h>

void kernel_main(void) 
{
	for (int _ = 0; _ < 20; _ ++) {
 		kprintf("Hello, kernel World!\n");
	}
}