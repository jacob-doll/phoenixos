#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#define KERNEL_OFFSET 0xC0000000

#ifdef __ASSEMBLER__ 
#define PHYSICAL_ADDR(x) (x - KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) (x + KERNEL_OFFSET)
#else
#include <stdint.h>
#define PHYSICAL_ADDR(x) ((uintptr_t)(a) & ~KERNEL_OFFSET)
#define VIRTUAL_ADDR(x) ((uintptr_t)(a) | KERNEL_OFFSET))
#endif // __ASSEMBLER__

#endif // _KERNEL_MEMORY_H