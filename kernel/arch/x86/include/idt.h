#ifndef _ARCH_X86_IDT_H
#define _ARCH_X86_IDT_H

#include <stdint.h>

#define IDT_GATE 0x8E

typedef struct idt_entry {
    uint16_t offset_lo;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idt_descriptor_t;

void init_idt(void);

#define IDT_ENTRY(__offset, __selector, __type)           \
(idt_entry_t){                                             \
    .offset_lo = (uint16_t)((__offset)&0xffff),           \
    .selector = __selector,                               \
    .zero = 0,                                            \
    .type_attr = __type,                                  \
    .offset_hi = (uint16_t)(((__offset) >> 16) & 0xffff), \
}

#endif // _ARCH_X86_IDT_H