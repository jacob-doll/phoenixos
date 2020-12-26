#include "idt.h"
#include "interrupts.h"
#include "ports.h"

#define IDT_NUM_ENTRIES 256

static idt_entry_t idt[IDT_NUM_ENTRIES];

static idt_descriptor_t idtr = {
    .size = sizeof(idt_entry_t) * IDT_NUM_ENTRIES - 1,
    .offset = (uint32_t)&idt[0],
};

void init_idt(void) {

    idt[0] = IDT_ENTRY((uint32_t)isr0, 0x8, IDT_GATE);
    idt[1] = IDT_ENTRY((uint32_t)isr1, 0x8, IDT_GATE);
    idt[2] = IDT_ENTRY((uint32_t)isr2, 0x8, IDT_GATE);
    idt[3] = IDT_ENTRY((uint32_t)isr3, 0x8, IDT_GATE);
    idt[4] = IDT_ENTRY((uint32_t)isr4, 0x8, IDT_GATE);
    idt[5] = IDT_ENTRY((uint32_t)isr5, 0x8, IDT_GATE);
    idt[6] = IDT_ENTRY((uint32_t)isr6, 0x8, IDT_GATE);
    idt[7] = IDT_ENTRY((uint32_t)isr7, 0x8, IDT_GATE);
    idt[8] = IDT_ENTRY((uint32_t)isr8, 0x8, IDT_GATE);
    idt[9] = IDT_ENTRY((uint32_t)isr9, 0x8, IDT_GATE);
    idt[10] = IDT_ENTRY((uint32_t)isr10, 0x8, IDT_GATE);
    idt[11] = IDT_ENTRY((uint32_t)isr11, 0x8, IDT_GATE);
    idt[12] = IDT_ENTRY((uint32_t)isr12, 0x8, IDT_GATE);
    idt[13] = IDT_ENTRY((uint32_t)isr13, 0x8, IDT_GATE);
    idt[14] = IDT_ENTRY((uint32_t)isr14, 0x8, IDT_GATE);
    idt[15] = IDT_ENTRY((uint32_t)isr15, 0x8, IDT_GATE);
    idt[16] = IDT_ENTRY((uint32_t)isr16, 0x8, IDT_GATE);
    idt[17] = IDT_ENTRY((uint32_t)isr17, 0x8, IDT_GATE);
    idt[18] = IDT_ENTRY((uint32_t)isr18, 0x8, IDT_GATE);
    idt[19] = IDT_ENTRY((uint32_t)isr19, 0x8, IDT_GATE);
    idt[20] = IDT_ENTRY((uint32_t)isr20, 0x8, IDT_GATE);
    idt[21] = IDT_ENTRY((uint32_t)isr21, 0x8, IDT_GATE);
    idt[22] = IDT_ENTRY((uint32_t)isr22, 0x8, IDT_GATE);
    idt[23] = IDT_ENTRY((uint32_t)isr23, 0x8, IDT_GATE);
    idt[24] = IDT_ENTRY((uint32_t)isr24, 0x8, IDT_GATE);
    idt[25] = IDT_ENTRY((uint32_t)isr25, 0x8, IDT_GATE);
    idt[26] = IDT_ENTRY((uint32_t)isr26, 0x8, IDT_GATE);
    idt[27] = IDT_ENTRY((uint32_t)isr27, 0x8, IDT_GATE);
    idt[28] = IDT_ENTRY((uint32_t)isr28, 0x8, IDT_GATE);
    idt[29] = IDT_ENTRY((uint32_t)isr29, 0x8, IDT_GATE);
    idt[30] = IDT_ENTRY((uint32_t)isr30, 0x8, IDT_GATE);
    idt[31] = IDT_ENTRY((uint32_t)isr31, 0x8, IDT_GATE);

    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    idt[32] = IDT_ENTRY((uint32_t)irq0, 0x8, IDT_GATE);
    idt[33] = IDT_ENTRY((uint32_t)irq1, 0x8, IDT_GATE);
    idt[34] = IDT_ENTRY((uint32_t)irq2, 0x8, IDT_GATE);
    idt[35] = IDT_ENTRY((uint32_t)irq3, 0x8, IDT_GATE);
    idt[36] = IDT_ENTRY((uint32_t)irq4, 0x8, IDT_GATE);
    idt[37] = IDT_ENTRY((uint32_t)irq5, 0x8, IDT_GATE);
    idt[38] = IDT_ENTRY((uint32_t)irq6, 0x8, IDT_GATE);
    idt[39] = IDT_ENTRY((uint32_t)irq7, 0x8, IDT_GATE);
    idt[40] = IDT_ENTRY((uint32_t)irq8, 0x8, IDT_GATE);
    idt[41] = IDT_ENTRY((uint32_t)irq9, 0x8, IDT_GATE);
    idt[42] = IDT_ENTRY((uint32_t)irq10, 0x8, IDT_GATE);
    idt[43] = IDT_ENTRY((uint32_t)irq11, 0x8, IDT_GATE);
    idt[44] = IDT_ENTRY((uint32_t)irq12, 0x8, IDT_GATE);
    idt[45] = IDT_ENTRY((uint32_t)irq13, 0x8, IDT_GATE);
    idt[46] = IDT_ENTRY((uint32_t)irq14, 0x8, IDT_GATE);
    idt[47] = IDT_ENTRY((uint32_t)irq15, 0x8, IDT_GATE);
    
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtr)); 
}