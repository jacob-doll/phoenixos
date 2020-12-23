#ifndef ARCH_X86_PAGING_H
#define ARCH_X86_PAGING_H

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef struct page_directory_entry {
    uint32_t present : 1;
    uint32_t read_write : 1;
    uint32_t user_supervisor: 1;
    uint32_t write_through: 1;
    uint32_t cache_disabled: 1;
    uint32_t accessed: 1;
    uint32_t ignored: 1;
    uint32_t page_size: 1;
    uint32_t ignored_2: 4;
    uint32_t page_table_addr: 20;
} __attribute__((packed)) page_directory_entry_t;

typedef struct page_table_entry {
    uint32_t present : 1;
    uint32_t read_write : 1;
    uint32_t user_supervisor: 1;
    uint32_t write_through: 1;
    uint32_t cache_disabled: 1;
    uint32_t accessed: 1;
    uint32_t dirty: 1;
    uint32_t ignored: 1;
    uint32_t global: 1;
    uint32_t ignored_2: 3;
    uint32_t physical_addr: 20;
} __attribute__((packed)) page_table_entry_t;

extern page_directory_entry_t page_directory[];

void map_kernel();

#endif // __ASSEMBLER__

#endif // ARCH_X86_PAGING_H