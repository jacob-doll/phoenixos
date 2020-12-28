#include <kernel/keyboard.h>
#include <kernel/kprintf.h>
#include <stdbool.h>

static bool keystate[128];
static key_handler handler;
static char ascii_codepoint[128] = {
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x00-0x07
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x08-0x0F
    '`', '1', '2', '3', '4', '5', '6', '7',         // 0x10-0x17
    '8', '9', '0', '-', '=', '\0', '\0', '\0',      // 0x18-0x1F
    '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u',        // 0x20-0x27
    'i', 'o', 'p', '[', ']', '\\', '\0', '\0',      // 0x28-0x2F
    '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j',        // 0x30-0x37
    'k', 'l', ';', '\'', '\0', '\0', '\0', '\0',    // 0x38-0x3F
    '\0', 'z', 'x', 'c', 'v', 'b', 'n', 'm',        // 0x40-0x47
    ',', '.', '/', '\0', '\0', '\0', '\0', '\0',    // 0x48-0x4F
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x50-0x57
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x58-0x5F
    '.', '0', '1', '2', '3', '4', '5', '6',         // 0x60-0x67
    '7', '8', '9', '+', '-', '*', '\0', '\0',       // 0x68-0x6F
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x70-0x77
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 0x78-0x7F
};

void keyboard_handle_key(uint8_t key, bool down) {
    keystate[key] = down;
    if (handler) {
        handler((key_event_t){ascii_codepoint[key], key, down});
    }
}

void keyboard_register_handler(key_handler key) {
    handler = key;
}
