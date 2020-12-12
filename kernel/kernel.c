#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/tty.h>
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
}