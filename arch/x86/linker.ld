ENTRY(_start)

SECTIONS
{
    . = 0x1000;

    .text : {
        /* *(.multiboot) */
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(COMMON)
        *(.bss)
    }
}