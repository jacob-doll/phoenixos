#include <kernel/kprintf.h>
#include <kernel/tty.h>

#include <stdbool.h> 
#include <stdint.h>
#include <stdarg.h>

void print_int(unsigned int num, int base) { 
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

void kprintf(const char* format, ...) {
    va_list list;
    va_start(list, format);

    while (*format != '\0') {
        if (*format == '%') {
            ++format;
            if (*format == 'c') {
                terminal_putchar(va_arg(list, int));
                ++format;
            } else if (*format == 's') {
                terminal_writestring(va_arg(list, char*));
                ++format;
            } else if (*format == 'd' || *format == 'i') {
                print_int(va_arg(list, int), 10);
                ++format;
            } else if (*format == 'o') {
                print_int(va_arg(list, unsigned int), 8);
                ++format;
            } else if (*format == 'x') {
                print_int(va_arg(list, unsigned int), 16);
                ++format;
            } else if (*format == 'u') {
                print_int(va_arg(list, unsigned int), 10);
                ++format;
            } else {
                terminal_putchar(*format);
                ++format;
            }
        } else {
            terminal_putchar(*format);
            ++format;
        }

    }

    va_end(list);
    return;
}