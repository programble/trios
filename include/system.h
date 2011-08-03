#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <types.h>
#include <modifiers.h>

noreturn halt();
noreturn reboot();

namespace Ports {
    u8 in(u16 port);
    void out(u16 port, u8 data);
}

#endif
