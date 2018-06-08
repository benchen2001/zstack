
CONFIG_STACK_SIZE = 1024;

MEMORY
{
    flash : ORIGIN = 0x00000000, LENGTH = 0x40000
    sram  : ORIGIN = 0x20000000, LENGTH = 0x20000
}

SECTIONS {
    .vectors : {
        . = ALIGN(4);
        *(.vectors*)
        . = ALIGN(4);
    } > flash

    .text : {
        . = ALIGN(4);
        *(.text*)
        . = ALIGN(4);
    } > flash

    .rodata : {
        *(.rodata*)
    } > flash

    .data : {
        *(.data*)
    } > sram

    .bss : {
        *(.bss*)
    } > sram

    .stack : {
        . = ALIGN(8);
        section_stack_start = .;

        . = . + CONFIG_STACK_SIZE;

        . = ALIGN(8);
        section_stack_end = .;
    } > sram
}

