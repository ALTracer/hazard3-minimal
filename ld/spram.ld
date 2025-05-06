MEMORY {
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 32K
	RAM   (rw)
 : ORIGIN = 0x00008000, LENGTH = 32K
}

ENTRY(_entry)

SECTIONS {
    .init :{
      . = ALIGN(4);
      KEEP(*(SORT_NONE(.init)))
      . = ALIGN(4);
    } >FLASH

    .text :{
      . = ALIGN(4);
      KEEP(*(.vector))
      *(.text .text*)
      . = ALIGN(4);
    } >FLASH

    .rodata :{
      *(.rodata .rodata*)
      *(.srodata .srodata*)
      . = ALIGN(4);
    } >FLASH

    .sdata :{
      . = ALIGN(4);
      _sdata = .;
    } >RAM

    .sidata :{
      . = ALIGN(4);
      _sidata = .;
    } >FLASH

    .data :{
      . = ALIGN(4);
      *(.data .data.*)
      __global_pointer$ = .;
      *(.sdata .sdata.*)
      . = ALIGN(4);
      _edata = .;
    } >RAM AT>FLASH

    .bss :{
      . = ALIGN(4);
      _sbss = .; PROVIDE(__bss_start = .);
      *(.sbss*)
      *(.bss*)
      . = ALIGN(4);
      _ebss = .; PROVIDE(__bss_end = .);
      _end = .; PROVIDE (end = .); /* _sbrk heap starts here */
    } >RAM
    PROVIDE(_estack = ORIGIN(RAM) + LENGTH(RAM));
}
