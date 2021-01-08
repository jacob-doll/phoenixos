#ifndef _KERNEL_BOOT_INFO_H
#define _KERNEL_BOOT_INFO_H

#include <stdint.h>

typedef struct mmap_entry {
    uint32_t base_lo;
	uint32_t base_hi;
	uint32_t length_lo;
	uint32_t length_hi;
	uint32_t type;
	uint32_t ACPI;
} __attribute__((packed)) mmap_entry_t;

typedef struct boot_info_table {
	uint32_t num_mmap_entries;
	mmap_entry_t* mmap_entries;
} boot_info_table_t;

#endif // _KERNEL_BOOT_INFO_H
