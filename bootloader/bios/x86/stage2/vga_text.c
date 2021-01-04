#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga_text.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0x000B8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	// if (y == VGA_HEIGHT - 1) {
	// 	size_t i;
	// 	for (i = 1; i < VGA_HEIGHT - 1; i++) {
	// 		memcpy(terminal_buffer + (i-1) * VGA_WIDTH,
	// 			   terminal_buffer + (i) * VGA_WIDTH,
	// 			   VGA_WIDTH * 2);
	// 	}
	// 	terminal_row = VGA_HEIGHT - 2;
	// } else {
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(c, color);
	// }
}

void terminal_putchar(char c) {
	if (c == '\n') {
		terminal_column = 0;
		++terminal_row;
	} else {
		unsigned char uc = c;
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_writeint(unsigned int num, int base) { 
    char buf[10];
    int i = 0;

    if (num == 0) {
        terminal_putchar('0');
        return;
    }

    while (num != 0) {
        int rem = num % base;
        buf[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num / base;
    }

    buf[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char c = *(buf + start);
        *(buf + start) = *(buf + end);
        *(buf + end) = c;
        start++;
        end--;
    }

    terminal_writestring(buf);
}