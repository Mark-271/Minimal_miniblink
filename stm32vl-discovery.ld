/* Linker script for ST STM32VLDISCOVERY (STM32F100RB, 128K flash, 8K RAM). */

/* Define memory regions. */
MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 128K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Include the common ld script. */

/* Enforce emmition of the vector table. */
EXTERN (vector_table)

/* Define the entry point of the output file. */
ENTRY(reset_handler)

/* Define sections. */
SECTIONS
{
	.text : {
		*(.vectors)	/* Vector table */
		*(.text*)	/* Program code */
		. = ALIGN(4);
		*(.rodata*)	/* Read-only data */
		. = ALIGN(4);
	} >rom

	. = ALIGN(4);
	_etext = .;

	data : {
		_data = .;
		*(.data*)	/* read-write initialized data */
		. = ALIGN(4);
		_edata = .;
	} >ram AT >rom
	_data_loadaddr = LOADADDR(.data);
	.bss : {
		*(.bss*)	/* Read-write initialized data */
		*(COMMO)
		. = ALIGN(4);
		_ebss = .;
	} >ram

	. = ALIGN(4);
	end = .;
}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));

