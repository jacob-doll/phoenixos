#include <stdbool.h>

#include "vga_text.h"
#include "ata_driver.h"
#include "elf.h"
#include "iso_9660.h"

#define DIR_BUFFER 0x10000
#define ELF_BUFFER 0x20000

static ata_device_t ata_primary_master = {.io_base = 0x1F0, .ctl_base = 0x3F6, .slavebit = 0};
static ata_device_t ata_primary_slave = {.io_base = 0x1F0, .ctl_base = 0x3F6, .slavebit = 1};
static ata_device_t ata_secondary_master = {.io_base = 0x170, .ctl_base = 0x376, .slavebit = 0};
static ata_device_t ata_secondary_slave = {.io_base = 0x170, .ctl_base = 0x376, .slavebit = 1};

typedef void (*kernel_entry)();
static kernel_entry entry;

static const char* KERNEL_FILE = "kernel.sys;1"; 

static bool streql(const char * l, const char * r, const int size) {
	if (!size) return false;
    for (int i = 0; i < size; i++) {
        if (l[i] != r[i]) return false;
    }
    return true;
}

void load_kernel(ata_device_t* dev, iso_9660_directory_t* dir, uint16_t sector_size) {
    atapi_read_sector(dev, dir->lba_le, (uint8_t*) ELF_BUFFER);
    elf_header_t* elf_hdr = (elf_header_t*) ELF_BUFFER;
    entry = (kernel_entry) elf_hdr->e_entry;
    uintptr_t elf_prg_hdr_addr = ELF_BUFFER + elf_hdr->e_phoff;
    for (uint16_t i = 0; i < elf_hdr->e_phnum; i++) {
        elf_program_header_t* elf_pgr_hdr = (elf_program_header_t*)(elf_prg_hdr_addr);
        uint32_t sector_offset = (elf_pgr_hdr->p_offset % sector_size) ? 
            ((elf_pgr_hdr->p_offset / sector_size) + 1) : 
            (elf_pgr_hdr->p_offset / sector_size);
        uint8_t num_sectors = (elf_pgr_hdr->p_filesz % sector_size) ? 
            ((elf_pgr_hdr->p_filesz / sector_size) + 1) : 
            (elf_pgr_hdr->p_filesz / sector_size);
        uintptr_t curr_load_buf = elf_pgr_hdr->p_paddr;
        terminal_writestring("Loading: ");
        terminal_writeint(num_sectors, 10);
        terminal_writestring(" sectors at: ");
        terminal_writeint(dir->lba_le + sector_offset, 10);
        terminal_writestring(" to: ");
        terminal_writeint(curr_load_buf, 0x10);
        terminal_writestring("\n");
        for(uint8_t i = 0; i < num_sectors; i++) {
            atapi_read_sector(dev, dir->lba_le + sector_offset, (uint8_t*) curr_load_buf);
            curr_load_buf += sector_size;
            sector_offset += 1;
        }
        elf_prg_hdr_addr += elf_hdr->e_phentsize;
    }
}

void start_load(ata_device_t* dev) {
    uintptr_t buf = DIR_BUFFER;
    uint16_t lbs;
    uint16_t num_sectors_read;
    iso_9660_directory_t* root_dir;
    iso_9660_directory_t* cur_dir;

    atapi_read_sector(dev, 0x10, (uint8_t*) buf);
    lbs = *((uint16_t*) (buf + 128));
    root_dir = (iso_9660_directory_t*) (buf + 156);
    buf += lbs;
    num_sectors_read = (root_dir->data_len_le % lbs) ? 
                       ((root_dir->data_len_le / lbs) + 1) : 
                       ((root_dir->data_len_le / lbs));
    for (unsigned i = 0; i < num_sectors_read; i++) {
        atapi_read_sector(dev, root_dir->lba_le + i, (uint8_t*) (buf + (lbs * i)));
    }
    cur_dir = (iso_9660_directory_t*) (buf);
    while (1) {
        if (streql(cur_dir->file_name, KERNEL_FILE, cur_dir->file_name_len)){
            break;
        }
        cur_dir = (iso_9660_directory_t*) ((uintptr_t)(cur_dir) + cur_dir->len);
    }
    terminal_writestring("Found kernel!\n");
    load_kernel(dev, cur_dir, lbs);
}

void boot_main() {
    terminal_initialize();
    terminal_writestring("BOOTLOAD MAIN\n");
    if (ata_detect_device(&ata_primary_master) == ATA_DEV_ATAPI) {
        start_load(&ata_primary_master);
    } else if (ata_detect_device(&ata_primary_slave) == ATA_DEV_ATAPI) {
        start_load(&ata_primary_slave);
    } else if (ata_detect_device(&ata_secondary_master) == ATA_DEV_ATAPI) {
        start_load(&ata_secondary_master);
    } else if (ata_detect_device(&ata_secondary_slave) == ATA_DEV_ATAPI) {
        start_load(&ata_secondary_slave);
    }
    terminal_writestring("Loaded Kernel!\n");
    entry();
}