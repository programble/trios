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
        x = Port::in(0x64);
    Port::out(0x64, 0xFE);
    halt();
}

bool recursive_panic = false;

noreturn _panic(const string message, const string function, const string file, const string line)
{
    Interrupts::disable();
    if (recursive_panic)
        halt();
    recursive_panic = true;

    // TODO: Output panic message

    // Simple keypress probing
    u8 init_scancode = Port::in(0x60);
    while (Port::in(0x60) == init_scancode);
    init_scancode = Port::in(0x60);
    while (true) {
        u8 scancode = Port::in(0x60);
        if (!(scancode & 0x80) && scancode != init_scancode)
            reboot();
    }
}
