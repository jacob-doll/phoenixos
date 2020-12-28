#include <stdbool.h>
#include <kernel/keyboard.h>
#include <kernel/kprintf.h>

#include "interrupts.h"
#include "ports.h"

static uint8_t keymap[128];

static void keyboard_callback(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);
    if (scancode <= 0x58) {
        keyboard_handle_key(keymap[scancode], true);
    } else if (scancode <= 0xD8) {
        keyboard_handle_key(keymap[scancode - 0x80], false);
    }
}

void keyboard_init() {
    register_interrupt_handler(IRQ1, keyboard_callback);

    keymap[0x01] = KEY_CODE_ESC;
    keymap[0x02] = KEY_CODE_1;
    keymap[0x03] = KEY_CODE_2;
    keymap[0x04] = KEY_CODE_3;
    keymap[0x05] = KEY_CODE_4;
    keymap[0x06] = KEY_CODE_5;
    keymap[0x07] = KEY_CODE_6;
    keymap[0x08] = KEY_CODE_7;
    keymap[0x09] = KEY_CODE_8;
    keymap[0x0A] = KEY_CODE_9;
    keymap[0x0B] = KEY_CODE_0;
    keymap[0x0C] = KEY_CODE_MINUS;
    keymap[0x0D] = KEY_CODE_EQUALS;
    keymap[0x0E] = KEY_CODE_BACKSPACE;
    keymap[0x0F] = KEY_CODE_TAB;

    keymap[0x10] = KEY_CODE_Q;
    keymap[0x11] = KEY_CODE_W;
    keymap[0x12] = KEY_CODE_E;
    keymap[0x13] = KEY_CODE_R;
    keymap[0x14] = KEY_CODE_T;
    keymap[0x15] = KEY_CODE_Y;
    keymap[0x16] = KEY_CODE_U;
    keymap[0x17] = KEY_CODE_I;
    keymap[0x18] = KEY_CODE_O;
    keymap[0x19] = KEY_CODE_P;
    keymap[0x1A] = KEY_CODE_BRACKET_LEFT;
    keymap[0x1B] = KEY_CODE_BRACKET_RIGHT;
    keymap[0x1C] = KEY_CODE_ENTER;
    keymap[0x1D] = KEY_CODE_LEFT_CTL;
    keymap[0x1E] = KEY_CODE_A;
    keymap[0x1F] = KEY_CODE_S;

    keymap[0x20] = KEY_CODE_D;
    keymap[0x21] = KEY_CODE_F;
    keymap[0x22] = KEY_CODE_G;
    keymap[0x23] = KEY_CODE_H;
    keymap[0x24] = KEY_CODE_J;
    keymap[0x25] = KEY_CODE_K;
    keymap[0x26] = KEY_CODE_L;
    keymap[0x27] = KEY_CODE_SEMI_COLON;
    keymap[0x28] = KEY_CODE_QUOTE;
    keymap[0x29] = KEY_CODE_GRAVE;
    keymap[0x2A] = KEY_CODE_LEFT_SHIFT;
    keymap[0x2B] = KEY_CODE_FORWARD_SLASH;
    keymap[0x2C] = KEY_CODE_Z;
    keymap[0x2D] = KEY_CODE_X;
    keymap[0x2E] = KEY_CODE_C;
    keymap[0x2F] = KEY_CODE_V;

    keymap[0x30] = KEY_CODE_B;
    keymap[0x31] = KEY_CODE_N;
    keymap[0x32] = KEY_CODE_M;
    keymap[0x33] = KEY_CODE_COMMA;
    keymap[0x34] = KEY_CODE_PERIOD;
    keymap[0x35] = KEY_CODE_BACK_SLASH;
    keymap[0x36] = KEY_CODE_RIGHT_SHIFT;
    keymap[0x37] = KEY_CODE_NUMPAD_ASTERISK;
    keymap[0x38] = KEY_CODE_LEFT_ALT;
    keymap[0x39] = KEY_CODE_SPACE;
    keymap[0x3A] = KEY_CODE_CAPS_LOCK;
    keymap[0x3B] = KEY_CODE_F1;
    keymap[0x3C] = KEY_CODE_F2;
    keymap[0x3D] = KEY_CODE_F3;
    keymap[0x3E] = KEY_CODE_F4;
    keymap[0x3F] = KEY_CODE_F5;

    keymap[0x40] = KEY_CODE_F6;
    keymap[0x41] = KEY_CODE_F7;
    keymap[0x42] = KEY_CODE_F8;
    keymap[0x43] = KEY_CODE_F9;
    keymap[0x44] = KEY_CODE_F10;
    keymap[0x45] = KEY_CODE_NUMLOCK;
    keymap[0x46] = KEY_CODE_SCROLLLOCK;
    keymap[0x47] = KEY_CODE_NUMPAD_7;
    keymap[0x48] = KEY_CODE_NUMPAD_8;
    keymap[0x49] = KEY_CODE_NUMPAD_9;
    keymap[0x4A] = KEY_CODE_NUMPAD_MINUS;
    keymap[0x4B] = KEY_CODE_NUMPAD_4;
    keymap[0x4C] = KEY_CODE_NUMPAD_5;
    keymap[0x4D] = KEY_CODE_NUMPAD_6;
    keymap[0x4E] = KEY_CODE_NUMPAD_PLUS;
    keymap[0x4F] = KEY_CODE_NUMPAD_1;

    keymap[0x50] = KEY_CODE_NUMPAD_2;
    keymap[0x51] = KEY_CODE_NUMPAD_3;
    keymap[0x52] = KEY_CODE_NUMPAD_0;
    keymap[0x53] = KEY_CODE_NUMPAD_PERIOD;
    keymap[0x54] = 0x0;
    keymap[0x55] = 0x0;
    keymap[0x56] = 0x0;
    keymap[0x57] = KEY_CODE_F11;
    keymap[0x58] = KEY_CODE_F12;

}