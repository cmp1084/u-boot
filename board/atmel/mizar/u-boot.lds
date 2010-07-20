OUTPUT_FORMAT("elf32-avr32", "elf32-avr32", "elf32-avr32")
OUTPUT_ARCH(avr32:uc)
ENTRY(_start)

MEMORY
{
  FLASH (rxai!w) : ORIGIN = 0x80000000, LENGTH = 0x00080000
  INTRAM (wxari) : ORIGIN = 0x00000004, LENGTH = 0x0000FFFC
  EXTRAM (wxari) : ORIGIN = 0xd0000000, LENGTH = 32M
}

SECTIONS
{
	. = ORIGIN(FLASH);
	_text = .;
	.text : {
		*(.text .exception.text .text.*)
	 } >FLASH AT>FLASH
	_etext = .;

	.rodata : {
		*(.rodata .rodata.*)
	} >FLASH AT>FLASH

	. = ALIGN(8);
	_data = .;
	.data : {
		*(.data .data.*)
	} >FLASH AT>FLASH

	. = ALIGN(4);
	__u_boot_cmd_start = .;
		.u_boot_cmd : { KEEP(*(.u_boot_cmd)) } >FLASH AT>FLASH
	__u_boot_cmd_end = .;

	. = ALIGN(4);
	_got = .;
		.got : { *(.got) } >FLASH AT>FLASH
	_egot = .;

	. = ALIGN(8);
	_edata = .;

	_bstart = .;
		.bss (NOLOAD) : { *(.bss .bss.*) } >FLASH AT>FLASH
	_bend = .;

	. = ALIGN(8);
	_end = .;
}
