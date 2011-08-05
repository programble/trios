CXX = clang++
ASM = nasm
LD = ld

TARGET = debug

KERNEL = trios.elf

override CXXINCLUDES += -Iinclude/
override CXXWARNINGS += -Wall -Wextra -Wunreachable-code -Wcast-qual -Wcast-align -Wswitch-enum -Wmissing-noreturn -Wwrite-strings -Wundef -Wpacked -Wredundant-decls -Winline -Wdisabled-optimization
override CXXFLAGS += -m32 -nostdinc -ffreestanding -fno-builtin -MMD
CXXACTION = -c

ifeq ($(TARGET),debug)
override CXXFLAGS += -ggdb -DDEBUG -O0
endif

override ASMFLAGS += -f elf

override LDFLAGS += -melf_i386 -nostdlib -T build/linker.ld

# Find all sources
CXXSOURCES := $(shell find src/ -name '*.cpp')
ASMSOURCES := $(shell find src/asm/ -name '*.asm')

CXXOBJECTS := $(CXXSOURCES:%.cpp=%.o)
ASMOBJECTS := $(ASMSOURCES:%.asm=%.o)

# Grab generated header dependencies
CXXDEPFILES := $(CXXOBJECTS:%.o=%.d)
-include $(CXXDEPFILES)

# No link
objects: $(ASMOBJECTS) $(CXXOBJECTS)

$(KERNEL): $(ASMOBJECTS) $(CXXOBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

src/asm/%.o: src/asm/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXWARNINGS) $(CXXINCLUDES) $(CXXACTION) $< -o $@
