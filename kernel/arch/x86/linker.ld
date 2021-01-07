SECTIONS
{
	start = 0x00100000;
    . = 0xC0100000;
	_kbegin = .;
	.text ALIGN (4K) : AT (ADDR (.text) - 0xC0000000)
	{
		_ktext_begin = .;
		*(.text);
		_ktext_end = .;
	}
	.rodata ALIGN (4K) : AT (ADDR (.rodata) - 0xC0000000)
	{
		_krodata_begin = .;
		*(.rodata)
		_krodata_end = .;
	}
	.data ALIGN (4K) : AT (ADDR (.data) - 0xC0000000)
	{
		_kdata_begin = .;
		*(.data);
		_kdata_end = .;
	}
	.bss ALIGN (4K) : AT (ADDR (.bss) - 0xC0000000)
	{
		_kbss_begin = .;
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
		_kbss_end = .;
	}
	_kend = .;
}