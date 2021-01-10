#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#define KERNEL_OFFSET 0xC0000000

#ifdef __ASSEMBLER__ 
#define PHYSICAL_ADDR(x) (x - KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) (x + KERNEL_OFFSET)
#else

#include <kernel/boot_info.h>

#include <stddef.h>
#include <stdint.h>

#define PHYSICAL_ADDR(x) ((uintptr_t)(x) & ~KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) ((uintptr_t)(x) | KERNEL_OFFSET))

#define MEM_USABLE 1
#define MEM_RESERVED 2
#define MEM_ACPI_RECLAIM 3
#define MEM_ACPI_NVS 4
#define MEM_BAD 5

#define PAGE_FRAME_SIZE 0x1000 // 4-KiB page length
#define MAX_PHYS_PAGES 0x100000 // 1024 * 1024

#define MAX_MEM_SIZE 0xFFFFFFFF // 4-GiB

typedef struct allocation {
    uintptr_t addr;
    size_t size;
} allocation_t;

void memory_init(boot_info_table_t* boot_info);
void memory_dump();

allocation_t memory_phys_alloc(size_t size);

uintptr_t memory_phys_used(uintptr_t addr);
void memory_phys_range_used(uintptr_t start, uintptr_t end);

uintptr_t memory_phys_free(uintptr_t addr);
void memory_phys_range_free(uintptr_t start, uintptr_t end);

#endif // __ASSEMBLER__

#endif // _KERNEL_MEMORY_H