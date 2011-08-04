#include <devices/output/text/serial.h>

namespace Devices { namespace Output { namespace Text { namespace Serial {
    const u16 port = 0x3F8;

    bool initialized = false;

    void init()
    {
        // No idea what all this does
        Port::out(port + 1, 0x00);
        Port::out(port + 3, 0x80);
        Port::out(port    , 0x03);
        Port::out(port + 1, 0x00);
        Port::out(port + 3, 0x03);
        Port::out(port + 2, 0xC7);
        Port::out(port + 4, 0x0B);

        initialized = true;
        print("serial output initialized\n");
    }

    void print(char c)
    {
        assert(initialized, "serial output not initialized");
        while (!(Port::in(port + 5) & 0x20));
        Port::out(port, c);
    }

    void print(const string s)
    {
        for (; *s; s++)
            print(*s);
    }
}}}}
