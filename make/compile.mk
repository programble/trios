CXX = clang++
ASM = nasm
LD = ld

TARGET = debug

KERNEL = trios.elf

override CXXINCLUDES += -Iinclude/
override CXXWARNINGS += -Wall -Wextra -Wunreachable-code -Wcast-qual -Wcast-align -Wswitch-enum -Wmissing-noreturn -Wwrite-strings -Wundef -Wpacked -Wredundant-decls -Winline -Wdisabled-optimization
override CXXFLAGS += -m32 -nostdinc -ffreestanding -fno-builtin -MMD

ifeq ($(TARGET),debug)
override CXXFLAGS += -ggdb -DDEBUG -O0
endif

override ASMFLAGS += -f elf

override LDFLAGS += -melf_i386 -nostdlib -T linker.ld

# Find all sources
CXXSOURCES := $(shell find src/ -name '*.cpp')
ASMSOURCES := $(shell find src/asm/ -name '*.asm')

CXXOBJECTS := $(CXXSOURCES:%.cpp=%.o)
ASMOBJECTS := $(ASMSOURCES:%.asm=%.o)

# Grab generated header dependencies
CXXDEPFILES := $(CXXOBJECTS:%.o=%.d)
-include $(CXXDEPFILES)

$(KERNEL): $(ASMOBJECTS) $(CXXOBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

src/asm/%.o: src/asm/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXWARNINGS) $(CXXINCLUDES) -c $< -o $@
