#include <system.h>

noreturn halt()
{
    while (true)
        asm("cli; hlt");
}

noreturn reboot()
{
    u8 x = 0x02;
    while (x & 0x02)
        x = Ports::in(0x64);
    Ports::out(0x64, 0xFE);
    halt();
}
