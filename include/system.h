#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <types.h>
#include <modifiers.h>

#define asm __asm__ __volatile__

noreturn halt();
noreturn reboot();

namespace Ports {
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
