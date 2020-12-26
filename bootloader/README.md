
# phoenixos Bootloader

The phoenixos Bootloader is heavily work-in-progress and only supports the kernel that I have developed thus far. There is no modularity at all and has hardcoded values that only work for the environment setup for it. I would not reccomend using this exact code to load another kernel but it can be modified to load other kernels.

## Features

- Can load a 32-bit x86 kernel from the sectors that follow the bootsector
- Loads the kernel into higher memory at 1Mb
- Calls the kernel entry point

## TODO

- Load sectors dynamically
- Locate kernel dynamically instead of statically defining location
- Get memory map from BIOS
- Get graphics information from bios
- ELF header parsing
- Provide collected information to kernel
- Multistage bootloader
