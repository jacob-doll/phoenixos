#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#define KERNEL_OFFSET 0xC0000000

#ifdef __ASSEMBLER__ 
#define PHYSICAL_ADDR(x) (x - KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) (x + KERNEL_OFFSET)
#else
#include <stdint.h>
#define PHYSICAL_ADDR(x) ((uintptr_t)(a) & ~KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) ((uintptr_t)(a) | KERNEL_OFFSET))
typedef struct mmap_entry {
    uint32_t base_lo;
	uint32_t base_hi;
	uint32_t length_lo;
	uint32_t length_hi;
	uint32_t type;
	uint32_t ACPI;
} __attribute__((packed)) mmap_entry_t;

#endif // __ASSEMBLER__

#endif // _KERNEL_MEMORY_H