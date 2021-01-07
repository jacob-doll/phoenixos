ENTRY(_start)

SECTIONS
{
    . = 0x7C00;
    .text : { 
        *(.bootsect.text)
        *(.text) 
    }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { 
        *(COMMON)
        *(.bss) 
    }
}