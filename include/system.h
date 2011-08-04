#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <types.h>
#include <modifiers.h>
#include <macros.h>

noreturn halt();
noreturn reboot();

noreturn _panic(const string message, const string function, const string file, const string line);
#define panic(x) _panic(x, __PRETTY_FUNCTION__, __FILE__, MACRO_STRING(__LINE__))
#define assert(x,m) if (!(x)) _panic("assert failed: " #x "\n" m, __PRETTY_FUNCTION__, __FILE__, MACRO_STRING(__LINE__))

namespace Port {
    inline u8 in(u16 port)
    {
        u8 ret;
        asm("inb %1, %0" : "=a" (ret) : "dN" (port));
        return ret;
    }
    inline void out(u16 port, u8 data)
    {
        asm("outb %1, %0" : : "dN" (port), "a" (data));
    }
}

namespace Interrupts {
    inline void enable() { asm("sti"); }
    inline void disable() { asm("cli"); }
}

#endif
