OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS
{
	. = 1M;
	.text : ALIGN(0x1000)
	{
		*(.multiboot)
		*(.text)
	}

	.data : { *(.data) }
	.bss  : { *(.bss) }
}
