#ifndef _ARCH_X86_GDT_H
#define _ARCH_X86_GDT_H

#include <stdint.h>

#define GDT_KERNEL_CODE 0b10011010
#define GDT_KERNEL_DATA 0b10010010
#define GDT_USER_CODE   0b11111010
#define GDT_USER_DATA   0b11110010
#define TSS_SEGMENT     0b10001001

#define GDT_FLAGS 0b1100
#define TSS_FLAGS 0b0000

typedef struct gdt_entry {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t limit_hi : 4;
    uint8_t flags : 4;
    uint8_t base_hi;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct tss_entry {
    uint32_t link;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t _[23];
} __attribute__((packed)) tss_entry_t;

void init_gdt(void);

#endif // _ARCH_X86_GDT_H