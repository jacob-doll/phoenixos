#include <kernel/memory.h>
#include <kernel/kprintf.h>

#include "paging.h"

extern int _kernel_start;
extern int _kernel_rodata_end;

void map_kernel() {

    page_directory_entry_t kernel_entry = page_directory[768];
    page_table_entry_t* current_entry = (page_table_entry_t*)(kernel_entry.page_table_addr * 0x1000);
    current_entry += 256;

    uint32_t kernel_start = (uint32_t)((uint8_t*)&_kernel_start);
    uint32_t kernel_rodata_end = (uint32_t)((uint8_t*)&_kernel_rodata_end);

#ifdef _KERNEL_VERBOSE
    kprintf("Setting %x-%x to read only.\n", kernel_start, kernel_rodata_end);
#endif

    uint32_t ptr = kernel_start;
    while (ptr < kernel_rodata_end) {
        current_entry->read_write = 0;
        ++current_entry;
        ptr += 0x1000;
    }

}