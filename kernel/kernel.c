#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/kprintf.h>
#include <kernel/keyboard.h>

void kernel_main(void) 
{
 	kprintf("Hello, kernel World!\n");
	init_keyboard();
	while(1) {}
}