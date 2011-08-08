global _gdt_flush
extern _gdt_ptr

_gdt_flush:
    lgdt [_gdt_ptr]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:_gdt_flush_end

_gdt_flush_end:
    ret
