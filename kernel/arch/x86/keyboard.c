#include <stdint.h>
#include <kernel/keyboard.h>
#include <kernel/kprintf.h>

#include "interrupts.h"
#include "ports.h"

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);
    kprintf("keyboard scancode: %x\n", scancode);
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}