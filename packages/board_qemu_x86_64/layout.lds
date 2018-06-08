CONFIG_STACK_SIZE = 512;

ENTRY(start)

MEMORY
{
    BOOTLOADER : ORIGIN = 0x1000, LENGTH = 0x6000
}

SECTIONS {

    .start : {
        *(.start*)
    } > BOOTLOADER

    .text : {
        . = ALIGN(4);
        *(.text*)
        . = ALIGN(4);
    } > BOOTLOADER

    .rodata : {
        *(.rodata*)
    } > BOOTLOADER

    .note : {
    	*(.note*)
    } > BOOTLOADER

    .data : {
        *(.data*)
    } > BOOTLOADER

    .bss : {
        section_bss_start = .;
        *(.bss*)
        section_bss_end = .;
    } > BOOTLOADER

    .stack : {
        . = ALIGN(8);
        section_stack_bottom = .;

        . = . + CONFIG_STACK_SIZE;

        . = ALIGN(8);
        section_stack_top = .;
    } > BOOTLOADER
}

