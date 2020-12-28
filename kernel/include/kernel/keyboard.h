#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define KEY_CODE_ESC             0x01
#define KEY_CODE_F1              0x02
#define KEY_CODE_F2              0x03
#define KEY_CODE_F3              0x04
#define KEY_CODE_F4              0x05
#define KEY_CODE_F5              0x06
#define KEY_CODE_F6              0x07
#define KEY_CODE_F7              0x08
#define KEY_CODE_F8              0x09
#define KEY_CODE_F9              0x0A
#define KEY_CODE_F10             0x0B
#define KEY_CODE_F11             0x0C
#define KEY_CODE_F12             0x0D

#define KEY_CODE_GRAVE           0x10
#define KEY_CODE_1               0x11
#define KEY_CODE_2               0x12
#define KEY_CODE_3               0x13
#define KEY_CODE_4               0x14
#define KEY_CODE_5               0x15
#define KEY_CODE_6               0x16
#define KEY_CODE_7               0x17
#define KEY_CODE_8               0x18
#define KEY_CODE_9               0x19
#define KEY_CODE_0               0x1A
#define KEY_CODE_MINUS           0x1B
#define KEY_CODE_EQUALS          0x1C
#define KEY_CODE_BACKSPACE       0x1D

#define KEY_CODE_TAB             0x20
#define KEY_CODE_Q               0x21
#define KEY_CODE_W               0x22
#define KEY_CODE_E               0x23
#define KEY_CODE_R               0x24 
#define KEY_CODE_T               0x25
#define KEY_CODE_Y               0x26
#define KEY_CODE_U               0x27
#define KEY_CODE_I               0x28
#define KEY_CODE_O               0x29
#define KEY_CODE_P               0x2A
#define KEY_CODE_BRACKET_LEFT    0x2B
#define KEY_CODE_BRACKET_RIGHT   0x2C
#define KEY_CODE_FORWARD_SLASH   0x2D

#define KEY_CODE_CAPS_LOCK       0x30
#define KEY_CODE_A               0x31
#define KEY_CODE_S               0x32
#define KEY_CODE_D               0x33
#define KEY_CODE_F               0x34
#define KEY_CODE_G               0x35
#define KEY_CODE_H               0x36
#define KEY_CODE_J               0x37
#define KEY_CODE_K               0x38
#define KEY_CODE_L               0x39
#define KEY_CODE_SEMI_COLON      0x3A
#define KEY_CODE_QUOTE           0x3B
#define KEY_CODE_ENTER           0x3C

#define KEY_CODE_LEFT_SHIFT      0x40
#define KEY_CODE_Z               0x41
#define KEY_CODE_X               0x42
#define KEY_CODE_C               0x43
#define KEY_CODE_V               0x44
#define KEY_CODE_B               0x45
#define KEY_CODE_N               0x46
#define KEY_CODE_M               0x47
#define KEY_CODE_COMMA           0x48
#define KEY_CODE_PERIOD          0x49
#define KEY_CODE_BACK_SLASH      0x4A
#define KEY_CODE_RIGHT_SHIFT     0x4B

#define KEY_CODE_LEFT_CTL        0x50
#define KEY_CODE_SUPER           0x51
#define KEY_CODE_LEFT_ALT        0x52
#define KEY_CODE_SPACE           0x53
#define KEY_CODE_RIGHT_ALT       0x54
#define KEY_CODE_LEFT_SUPER      0x55
#define KEY_CODE_OPTIONS         0x56
#define KEY_CODE_RIGHT_CTL       0x57

#define KEY_CODE_NUMPAD_PERIOD   0x60
#define KEY_CODE_NUMPAD_0        0x61
#define KEY_CODE_NUMPAD_1        0x62
#define KEY_CODE_NUMPAD_2        0x63
#define KEY_CODE_NUMPAD_3        0x64
#define KEY_CODE_NUMPAD_4        0x65
#define KEY_CODE_NUMPAD_5        0x66
#define KEY_CODE_NUMPAD_6        0x67
#define KEY_CODE_NUMPAD_7        0x68
#define KEY_CODE_NUMPAD_8        0x69
#define KEY_CODE_NUMPAD_9        0x6A
#define KEY_CODE_NUMPAD_PLUS     0x6B
#define KEY_CODE_NUMPAD_MINUS    0x6C
#define KEY_CODE_NUMPAD_ASTERISK 0x6D

#define KEY_CODE_NUMLOCK         0x70
#define KEY_CODE_SCROLLLOCK      0x71
typedef struct key_event {
    char ascii;
    uint8_t keycode;
    bool down;
} key_event_t;

void keyboard_init();
void keyboard_handle_key(uint8_t key, bool down);

typedef void (*key_handler)(key_event_t key);
void keyboard_register_handler(key_handler key);

#endif __KERNEL_KEYBOARD_H