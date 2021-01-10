#include <kernel/memory.h>
#include <kernel/kprintf.h>

#include <stdint.h>
#include <stdbool.h>

static uint8_t PHSYICAL_PAGES[MAX_PHYS_PAGES / 8]; 
static size_t TOTAL_MEMORY;
static size_t USED_MEMORY;
static uintptr_t CURR_ALLOC_PTR;

extern int _kbegin;
extern int _kend;

void memory_init(boot_info_table_t *boot_info) {
    size_t i;
    // initialize memory map
    for (i = 0; i < 1024 * 1024 / 8; i++) {
        PHSYICAL_PAGES[i] = 0xFF;
    }

    // free up all usable memory; memory map received from bootloader
    for (i = 0; i < boot_info->num_mmap_entries; i++) {
        mmap_entry_t entry = boot_info->mmap_entries[i];
        if (entry.type == MEM_USABLE) {
            TOTAL_MEMORY += entry.length_lo;
            USED_MEMORY += entry.length_lo;
            memory_phys_range_free(entry.base_lo, (entry.base_lo + entry.length_lo));
        }
    }

    // make sure that the kernels physical memory cannot be used
    memory_phys_range_used(PHYSICAL_ADDR((uintptr_t)((uint8_t*)&_kbegin)), 
                           PHYSICAL_ADDR((uintptr_t)((uint8_t*)&_kend)));

    CURR_ALLOC_PTR = PHYSICAL_ADDR((uintptr_t)((uint8_t*)&_kend));
    if (CURR_ALLOC_PTR % PAGE_FRAME_SIZE) {
        CURR_ALLOC_PTR = ((CURR_ALLOC_PTR / PAGE_FRAME_SIZE) + 1) * PAGE_FRAME_SIZE;
    }
}

void memory_dump() {
    kprintf("TOTAL MEMORY %u\n", TOTAL_MEMORY);
    kprintf("USED MEMORY %u\n", USED_MEMORY);
    kprintf("CURRENT ALLOCATION %x\n", CURR_ALLOC_PTR);
}

static bool is_page_used(uintptr_t page_addr) {
    uint32_t page = page_addr / PAGE_FRAME_SIZE;
    return PHSYICAL_PAGES[page / 8] & (1 << (page % 8));
}

allocation_t memory_phys_alloc(size_t size) {
    uintptr_t addr = CURR_ALLOC_PTR;
    uintptr_t alloc_addr = addr;
    uintptr_t end_addr = alloc_addr + size;
    while (addr < MAX_MEM_SIZE) {
        if (is_page_used(addr)) {
            alloc_addr = addr + PAGE_FRAME_SIZE;
            end_addr = alloc_addr + size;
        }

        if (addr >= end_addr) break;

        addr += PAGE_FRAME_SIZE;
    }
    memory_phys_range_used(alloc_addr, alloc_addr + size);
    CURR_ALLOC_PTR = addr;
    return (allocation_t){.addr = alloc_addr, .size = size};
}


uintptr_t memory_phys_used(uintptr_t addr) {
    uint32_t page = (addr % PAGE_FRAME_SIZE) ?
        ((addr / PAGE_FRAME_SIZE) + 1) :
        ((addr / PAGE_FRAME_SIZE));

    PHSYICAL_PAGES[page / 8] |= (1 << (page % 8));
    USED_MEMORY += PAGE_FRAME_SIZE;
    
    return addr;
}

void memory_phys_range_used(uintptr_t start, uintptr_t end) {
    while (start < end) {
        memory_phys_used(start);
        start += PAGE_FRAME_SIZE;
    }
}

uintptr_t memory_phys_free(uintptr_t addr) {
    uint32_t page = (addr % PAGE_FRAME_SIZE) ?
        ((addr / PAGE_FRAME_SIZE) + 1) :
        ((addr / PAGE_FRAME_SIZE));

    PHSYICAL_PAGES[page / 8] &= ~(1 << (page % 8));
    USED_MEMORY -= PAGE_FRAME_SIZE;
    
    return addr;
}

void memory_phys_range_free(uintptr_t start, uintptr_t end) {
    while (start < end) {
        memory_phys_free(start);
        start += PAGE_FRAME_SIZE;
    }
}
