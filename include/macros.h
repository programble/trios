#ifndef _MACROS_H_
#define _MACROS_H_

// Meta macros
#define STRING(x) #x
#define MACRO_STRING(x) STRING(x)

#define NULL ((void*) 0)

#define asm __asm__ __volatile__

#endif
