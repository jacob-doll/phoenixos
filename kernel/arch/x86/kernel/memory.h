#ifndef ARCH_I386_MEMORY_H
#define ARCH_I386_MEMORY_H

#include <stdint.h>

typedef struct mmap_entry {
    uint32_t base_lo; // base address uint64_t
	uint32_t base_hi;
	uint32_t length_lo; // length uint64_t
	uint32_t length_hi;
	uint32_t type; // entry Type
	uint32_t ACPI; // extended
} __attribute__((packed)) mmap_entry_t;

typedef struct mmap_table {
    uint32_t size;
    uintptr_t *begin;
} __attribute__((packed)) mmap_table_t;

#endif // ARCH_I386_MEMORY_H