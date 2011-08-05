#pragma once

#include <system.h>

namespace Devices { namespace Output { namespace Text { namespace Console {
    enum Color {
        black,
        blue,
        green,
        cyan,
        red,
        magenta,
        brown,
        gray,
        bright_black, // Yeah... About that... (FIXME: Dark gray?)
        bright_blue,
        bright_green,
        bright_cyan,
        bright_red,
        bright_magenta,
        bright_brown, // FIXME: Yellow?
        bright_gray // FIXME: White?
    };

    extern Color foreground;
    extern Color background;

    extern bool initialized;

    void init();

    void print(char c);
    void print(const string s);

    void put(char c, u8 x, u8 y);
    void put(const string s, u8 x, u8 y);

    void clear();
}}}}
