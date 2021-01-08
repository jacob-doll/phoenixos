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

#define PHYSICAL_ADDR(x) ((uintptr_t)(a) & ~KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) ((uintptr_t)(a) | KERNEL_OFFSET))

#define MEM_USABLE 1
#define MEM_RESERVED 2
#define MEM_ACPI_RECLAIM 3
#define MEM_ACPI_NVS 4
#define MEM_BAD 5

void memory_init(boot_info_table_t* boot_info);
void memory_dump();

#endif // __ASSEMBLER__

#endif // _KERNEL_MEMORY_H