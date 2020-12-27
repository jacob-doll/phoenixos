#include <kernel/kprintf.h>

#include "pit.h"
#include "ports.h"
#include "interrupts.h"

static uint32_t tick = 0;

static void pit_callback(registers_t regs) {
    tick++;
    kprintf("Tick: %u\n", tick);
}

void pit_init(uint32_t freq) {

    register_interrupt_handler(IRQ0, pit_callback);

    uint16_t divisor = 1193182 / freq;

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, (uint8_t)(divisor & 0xFF));
    port_byte_out(0x40, (uint8_t)((divisor >> 8) & 0xFF));
}
