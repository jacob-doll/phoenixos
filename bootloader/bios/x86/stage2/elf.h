#ifndef _BOOT_ELF_H
#define _BOOT_ELF_H

#include <stdint.h>

#define EI_MAG0 0x00
#define EI_MAG1 0x01
#define EI_MAG2 0x02
#define EI_MAG3 0x03
#define EI_CLASS 0x04
#define EI_DATA 0x05
#define EI_VERSION 0x06
#define EI_OSABI 0x07
#define EI_ABIVERSION 0x08
#define EI_LENGTH 0x10


typedef struct elf_header {
    uint8_t e_ident[EI_LENGTH]; // identity params
    uint32_t e_type: 16;        // object file type
    uint32_t e_machine: 16;     // machine instruction set
    uint32_t e_version;         // same as EI_VERSION
    uint32_t e_entry;           // memory entry point
    uint32_t e_phoff;           // start of program headers
    uint32_t e_shoff;           // start of section headers
    uint32_t e_flags;           // flags
    uint32_t e_ehsize: 16;      // size of this header
    uint32_t e_phentsize: 16;   // size of program headers
    uint32_t e_phnum: 16;       // number of program headers
    uint32_t e_shentsize: 16;   // size of section headers
    uint32_t e_shnum: 16;       // number of section headers
    uint32_t e_shstrndx: 16;    // section header string table index
} elf_header_t;

typedef struct elf_program_header {
    uint32_t p_type;   // type of the segment
    uint32_t p_offset; // offset of segment in the file image
    uint32_t p_vaddr;  // virtual address of segment in memory
    uint32_t p_paddr;  // physical address of segment in memory
    uint32_t p_filesz; // size in bytes of segment in file image
    uint32_t p_memsz;  // size in bytes of segment in memory
    uint32_t p_flags;  // flags
    uint32_t p_align;  // alignment
} elf_program_header_t;

#endif // _BOOT_ELF_H