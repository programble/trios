#ifndef _MODIFIERS_H_
#define _MODIFIERS_H_

#define always_inline __attribute__((gnu_inline,always_inline)) static inline
#define deprecated __attribute__((deprecated))
#define noreturn __attribute__((noreturn)) void
#define unused __attribute__((unused))

#endif
