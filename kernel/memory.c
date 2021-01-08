#include <kernel/memory.h>
#include <kernel/kprintf.h>

#include <stdint.h>
#include <stdbool.h>

static uint8_t PHSYICAL_PAGES[1024 * 1024 / 8]; 

static void map_page_range(uint32_t start, uint32_t end) {
    for (uint32_t page = start; page < end; page++) {
        PHSYICAL_PAGES[page / 8] &= ~(1 << (page % 8));
    }
}

static bool is_page_used(uint32_t page) {
    return PHSYICAL_PAGES[page / 8] & (1 << (page % 8));
}

void memory_init(boot_info_table_t *boot_info) {
    size_t i;
    for (i = 0; i < 1024 * 1024 / 8; i++) {
        PHSYICAL_PAGES[i] = 0xFF;
    }
    for (i = 0; i < boot_info->num_mmap_entries; i++) {
        mmap_entry_t entry = boot_info->mmap_entries[i];
        if (entry.type == MEM_USABLE) {
            kprintf("Mapping phys range: %x-%x\n", entry.base_lo, entry.base_lo + entry.length_lo);
            uint32_t start_page = entry.base_lo / 0x1000;
            uint32_t end_page = (entry.base_lo + entry.length_lo) / 0x1000;
            map_page_range(start_page, end_page);
        }
    }
}

void memory_dump() {
    bool last_page = true;
    for (uint32_t i = 0; i < 1024 * 1024; i++) {
        bool used = is_page_used(i);
        if (!used && (used != last_page)) {
            kprintf("Mem range free: %x-", i * 0x1000);
        }
        if (used && (used != last_page)) {
            kprintf("%x\n", i * 0x1000);
        }
        last_page = used;
    }
}
