#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/boot_info.h>
#include <kernel/memory.h>
#include <kernel/kprintf.h>
#include <kernel/keyboard.h>

void key_event(key_event_t key) {
	kprintf("key event: %x %c\n", key.keycode, key.ascii);
}

void kernel_main(boot_info_table_t *boot_info) 
{
 	kprintf("Hello, kernel World!\n");
	memory_init(boot_info);
	memory_dump();
	keyboard_init();
	keyboard_register_handler(key_event);
	while(1) {}
}