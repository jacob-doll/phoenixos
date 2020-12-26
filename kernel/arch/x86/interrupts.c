#include <kernel/kprintf.h>

#include "interrupts.h"
#include "ports.h"

static isr_t interrupt_handlers[256];

static char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void register_interrupt_handler(uint8_t index, isr_t handler) {
    interrupt_handlers[index] = handler;
}

void common_handler(registers_t regs) {

    if (regs.int_no > 31) {
        if (regs.int_no >= 40) {
            port_byte_out(0xA0, 0x20);
        }
        port_byte_out(0x20, 0x20);
    }

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}