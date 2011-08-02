CC=clang
ASM=nasm
LD=ld

KERNEL=trios.elf

override CINCLUDES += -Iinclude/
override CWARNINGS += -Wall -Wextra -Wunreachable-code -Wcast-qual -Wcast-align -Wswitch-enum -Wmissing-noreturn -Wwrite-strings -Wundef -Wpacked -Wredundant-decls -Winline -Wdisabled-optimization -Wbad-function-cast
# TODO: Separate debug options
override CFLAGS += -m32 -std=c99 -nostdinc -ffreestanding -fno-builtin -MMD -ggdb -DDEBUG -O0

override ASFLAGS += -f elf

override LDFLAGS += -melf_i386 -nostdlib -T linker.ld

# Find all sources
CSOURCES := $(shell find src/ -name '*.c')
ASOURCES := $(shell find src/asm/ -name '*.asm')

COBJECTS := $(CSOURCES:%.c=%.o)
AOBJECTS := $(ASOURCES:%.asm=%.o)

# Grab generated header dependencies
-include $(COBJECTS:%.o=%.d)

# Linking
$(KERNEL): $(AOBJECTS) $(COBJECTS)
	$(LD) $(LDFLAGS) $(AOBJECTS) $(COBJECTS) -o $@

src/asm/%.o: src/asm/%.asm
	$(ASM) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CWARNINGS) $(CINCLUDES) -c $< -o $@
