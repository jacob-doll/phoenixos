
# phoenixos Kernel

The phoenixos Kernel is fundamentally lacking at the moment. All you can realistically do is print text to the VGA buffer via a compiled kernel. This is a work in progress though and I plan to add the features below.

## Directory

- /arch
  - architecture dependent sources
- /include
  - headers for kernel sources

## Features

- Print null-terminated strings to a VGA buffer
- Global constructors

## Memory Map

| Memory Range            | Type   |
| :---------------------- | :----- |
| 0x00000000 - 0xBFFFFFFF | User   |
| 0xC0000000 - 0xFFFFFFFF | Kernel |

## TODO

- Paging/Memory Management
- Implement a stack smash protector
- Multithreading support
- Keyboard support
- Debugger
- Filesystem
- Much much more...
