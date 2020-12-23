ENTRY(_start)

SECTIONS
{
    /* . = 0x100000;

    .text : {
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
    } */

    . = 0xC0100000;
	_kernel_start = .;
	.text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		*(.text)
	}
	_kernel_text_end = .;
	.rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}
	_kernel_rodata_end = .;
	.data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}
	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
	_kernel_end = .;
}