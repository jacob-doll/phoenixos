#include "vga_text.h"
#include "ata_driver.h"
#include "elf.h"

#define SECTOR_SIZE 512

static ata_device_t ata_primary_master = {.io_base = 0x1F0, .ctl_base = 0x3F6, .slavebit = 0};
// static ata_device_t ata_primary_slave = {.io_base = 0x1F0, .ctl_base = 0x3F6, .slavebit = 1};
// static ata_device_t ata_secondary_master = {.io_base = 0x170, .ctl_base = 0x376, .slavebit = 0};
// static ata_device_t ata_secondary_slave = {.io_base = 0x170, .ctl_base = 0x376, .slavebit = 1};

static uintptr_t elf_hdr_addr = 0x10000;
static uintptr_t elf_prg_hdr_addr;
static uintptr_t curr_load_buf;

void load_kernel(void) {
    uint32_t sector_start = 0;
    elf_header_t* elf_hdr = NULL;
    while (1) {
        ata_read_sector(&ata_primary_master, sector_start, (uint8_t*) elf_hdr_addr);
        elf_hdr = (elf_header_t*) elf_hdr_addr;
        if (elf_hdr->e_ident[EI_MAG0] == 0x7F &&
            elf_hdr->e_ident[EI_MAG1] == 0x45 &&
            elf_hdr->e_ident[EI_MAG2] == 0x4C &&
            elf_hdr->e_ident[EI_MAG3] == 0x46) {
            break;
        }
        sector_start++;
    }
    terminal_writestring("Found Elf in sector: ");
    terminal_writeint(sector_start, 10);
    terminal_writestring("\n");
    elf_prg_hdr_addr = elf_hdr_addr + elf_hdr->e_phoff;
    terminal_writestring("First program header at: ");
    terminal_writeint(elf_prg_hdr_addr, 16);
    terminal_writestring("\n");
    for (uint16_t i = 0; i < elf_hdr->e_phnum; i++) {
        elf_program_header_t* elf_pgr_hdr = (elf_program_header_t*)(elf_prg_hdr_addr);
        uint32_t sector_offset = (elf_pgr_hdr->p_offset % SECTOR_SIZE) ? 
            ((elf_pgr_hdr->p_offset / SECTOR_SIZE) + 1) : 
            (elf_pgr_hdr->p_offset / SECTOR_SIZE);
        uint8_t num_sectors = (elf_pgr_hdr->p_filesz % SECTOR_SIZE) ? 
            ((elf_pgr_hdr->p_filesz / SECTOR_SIZE) + 1) : 
            (elf_pgr_hdr->p_filesz / SECTOR_SIZE);
        terminal_writestring("Starting at: ");
        terminal_writeint(sector_start + sector_offset, 10);
        terminal_writestring(", reading num sectors: ");
        terminal_writeint(num_sectors, 10);
        terminal_writestring(", to address: ");
        terminal_writeint(elf_pgr_hdr->p_paddr, 16);
        terminal_writestring("\n");
        curr_load_buf = elf_pgr_hdr->p_paddr;
        for(uint8_t i = 0; i < num_sectors; i++) {
            ata_read_sector(&ata_primary_master, sector_start + sector_offset, (uint8_t*) curr_load_buf);
            curr_load_buf += SECTOR_SIZE;
            sector_offset += 1;
        }
        elf_prg_hdr_addr += elf_hdr->e_phentsize;
    }
}

typedef void (*kernel_entry)();

void boot_main(void) {
    terminal_initialize();
    terminal_writestring("Bootloader Stage 2!\n");
    load_kernel();
    terminal_writestring("Loaded Kernel!\n");
    kernel_entry entry = (kernel_entry)0x100000;
    entry();
}