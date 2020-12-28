#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
#include <kernel/kprintf.h>
#include <kernel/keyboard.h>

void key_event(key_event_t key) {
	kprintf("key event: %x %c\n", key.keycode, key.ascii);
}

void kernel_main(void) 
{
 	kprintf("Hello, kernel World!\n");
	keyboard_init();
	keyboard_register_handler(key_event);
	while(1) {}
}