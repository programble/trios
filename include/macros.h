#pragma once

// Meta macros
#define STRING(x) #x
#define MACRO_STRING(x) STRING(x)

#define NULL ((void*) 0)

#define asm __asm__ __volatile__
