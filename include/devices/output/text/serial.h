#pragma once

#include <system.h>

// Stupid C++
namespace Devices { namespace Output { namespace Text { namespace Serial {
    extern bool initialized;

    void init();
    void print(char c);
    void print(const string s);
}}}}
