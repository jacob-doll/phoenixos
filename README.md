
# phoenixos

This project follows my progression as I learn more about operating system development. I will keep this document updated with the things I have learned and the struggles I have dealt with.

## Directory Structure

- [/bootloader](/bootloader/README.md)
  - Contains the bootloader code
- [/kernel](/kernel/README.md)
  - Contains all kernel sources

## Struggles I have dealt with

- Turns out that int=13h ah=2h does not like non floppy drives so when I was using standard CHS loading I had to pass in -fda to qemu.

- When loading a disk to a buffer using int=13h ah=42h make sure that the start sector (es+8) is not zero or you will call your boot code indefinately.

- When you put cli (which turns off hardware interrupts) you shouldn't be surpised when your keyboard controller does not work.
