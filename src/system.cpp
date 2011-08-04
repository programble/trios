#include <system.h>

noreturn halt()
{
    __asm__ __volatile__("cli; hlt");
    while (true);
}

noreturn reboot()
{
    u8 x = 0x02;
    while (x & 0x02)
        x = Ports::in(0x64);
    Ports::out(0x64, 0xFE);
    halt();
}

namespace Ports
{
    u8 in(u16 port)
    {
        u8 ret;
        __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "dN" (port));
        return ret;
    }

    void out(u16 port, u8 data)
    {
        __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (data));
    }
}
