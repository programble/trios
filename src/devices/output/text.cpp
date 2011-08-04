#include <devices/output/text.h>

#include <devices/output/text/serial.h>

namespace Devices { namespace Output { namespace Text {
    void print(char c)
    {
        if (Serial::initialized)
            Serial::print(c);
    }

    void print(const string s)
    {
        if (Serial::initialized)
            Serial::print(s);
    }
}}}
