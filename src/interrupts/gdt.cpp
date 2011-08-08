#include <interrupts/gdt.h>
#include <devices/output/text.h>

namespace Interrupts { namespace Gdt {
    struct Entry {
        u16 limit_low;
        u16 base_low;
        u8 base_middle;
        u8 access;
        u8 granularity;
        u8 base_high;
    };

    struct Pointer {
        u16 limit;
        u32 base;
    } __attribute__((packed));

    extern "C" Pointer _gdt_ptr;
    Pointer _gdt_ptr; // This feels stupid, but works

    Entry gdt[3];

    extern "C" void _gdt_flush();

    void set_gate(u32 num, u64 base, u64 limit, u8 access, u8 gran)
    {
        gdt[num].base_low = (base & 0xFFFF);
        gdt[num].base_middle = (base >> 16) & 0xFF;
        gdt[num].base_high = (base >> 24) & 0xFF;
        gdt[num].limit_low = (limit & 0xFFFF);
        gdt[num].granularity = (limit >> 16) & 0x0F;
        gdt[num].granularity |= ((u8) gran & 0xF0);
        gdt[num].access = access;
    }

    void init()
    {
        _gdt_ptr.limit = (sizeof(Entry) * 3) - 1;
        _gdt_ptr.base = (u32) &gdt;

        set_gate(0, 0, 0, 0, 0);
        set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
        set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

        _gdt_flush();
    }
}}
