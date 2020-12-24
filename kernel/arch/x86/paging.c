#include <kernel/memory.h>
#include <kernel/kprintf.h>

#include "paging.h"

extern int _kbegin;
extern int _ktext_begin;
extern int _ktext_end;
extern int _krodata_begin;
extern int _krodata_end;
extern int _kdata_begin;
extern int _kdata_end;
extern int _kbss_begin;
extern int _kbss_end;
extern int _kend;

void map_kernel() {

    page_directory_entry_t kernel_entry = page_directory[768];
    page_table_entry_t* current_entry = (page_table_entry_t*)(kernel_entry.page_table_addr * 0x1000);
    current_entry += 256;

    uint32_t kbegin = (uint32_t)((uint8_t*)&_kbegin);
    uint32_t krodata_end = (uint32_t)((uint8_t*)&_krodata_end);

#ifdef _KERNEL_VERBOSE
    kprintf("Mapping %x-%x\n", (uint8_t*)&_kbegin, (uint8_t*)&_kend);
    kprintf(".text %x-%x\n", (uint8_t*)&_ktext_begin, (uint8_t*)&_ktext_end);
    kprintf(".rodata %x-%x\n", (uint8_t*)&_krodata_begin, (uint8_t*)&_krodata_end);
    kprintf(".data %x-%x\n", (uint8_t*)&_kdata_begin, (uint8_t*)&_kdata_end);
    kprintf(".bss %x-%x\n", (uint8_t*)&_kbss_begin, (uint8_t*)&_kbss_end);
#endif

    uint32_t ptr = kbegin;
    while (ptr < krodata_end) {
        current_entry->read_write = 0;
        ++current_entry;
        ptr += 0x1000;
    }

}