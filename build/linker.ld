ENTRY (loader)
SECTIONS
{
    . = 0x00100000;
    link_start = .;

    .mbheader : {
        *(.mbheader)
    }

    .text : {
        *(.text)
    }

    .rodata ALIGN (0x1000) : {
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
        *(.data)
    }

    .bss : {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }

    link_end = .;
}
