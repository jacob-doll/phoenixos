#include "gdt.h"

#define GDT_NUM_ENTRIES 6

extern void load_gdt(uint32_t);

static gdt_entry_t gdt[GDT_NUM_ENTRIES];

static gdt_descriptor_t gdtr = {
    .size = sizeof(struct gdt_entry) * GDT_NUM_ENTRIES,
    .offset = (uint32_t)&gdt[0],
};

static tss_entry_t tss = {
    .link = 0,
    .esp0 = 0,
    .ss0  = 0x10
};

static gdt_entry_t create_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt_entry_t entry = {
        .limit_lo = (uint16_t)((limit) & 0x0000ffff),
        .base_lo = (uint16_t)((base) & 0x0000ffff),
        .base_mid = (uint8_t)((base >> 16) & 0x000000ff),
        .access_byte = access,
        .limit_hi = (uint8_t)((limit) & 0x000f0000),
        .flags = flags,
        .base_hi = (uint8_t)((base) & 0xff000000)
    };
    return entry;
}

void init_gdt(void) {
    gdt[0] = create_gdt_entry(0, 0, 0, 0);
    gdt[1] = create_gdt_entry(0, 0xffffffff, GDT_KERNEL_CODE, GDT_FLAGS);
    gdt[2] = create_gdt_entry(0, 0xffffffff, GDT_KERNEL_DATA, GDT_FLAGS);
    gdt[3] = create_gdt_entry(0, 0xffffffff, GDT_USER_CODE, GDT_FLAGS);
    gdt[4] = create_gdt_entry(0, 0xffffffff, GDT_USER_DATA, GDT_FLAGS);
    gdt[5] = create_gdt_entry((uint32_t)&tss, (uint32_t)sizeof(tss_entry_t), TSS_SEGMENT, TSS_FLAGS);

    load_gdt((uint32_t)&gdtr);
}