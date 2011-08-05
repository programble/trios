#include <devices/output/text.h>

#include <devices/output/text/serial.h>
#include <devices/output/text/console.h>

namespace Devices { namespace Output { namespace Text {
    void print(char c)
    {
        if (Serial::initialized)
            Serial::print(c);
        if (Console::initialized)
            Console::print(c);
    }

    void print(const string s)
    {
        if (Serial::initialized)
            Serial::print(s);
        if (Console::initialized)
            Console::print(s);
    }
}}}
