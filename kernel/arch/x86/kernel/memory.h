#ifndef ARCH_I386_MEMORY_H
#define ARCH_I386_MEMORY_H

#include <stdint.h>

typedef struct mmap_entry {
    uint32_t base_lo;
	uint32_t base_hi;
	uint32_t length_lo;
	uint32_t length_hi;
	uint32_t type;
	uint32_t ACPI;
} __attribute__((packed)) mmap_entry_t;

#endif // ARCH_I386_MEMORY_H