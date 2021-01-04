#ifndef _BOOT_PORTS_H
#define _BOOT_PORTS_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

static inline void outb(uint16_t port, uint8_t data) {
    asm volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

static inline uint16_t inw(uint16_t port) {
    uint16_t result;
    asm volatile("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

static inline void outw(uint16_t port, uint16_t data) {
    asm volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}

static inline void insw(uint16_t port, uint8_t* data, uint32_t size) {
    asm volatile("rep insw" : "+D" (data), "+c" (size) : "d" (port) : "memory");
}


#endif // _BOOT_PORTS_H