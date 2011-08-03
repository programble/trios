# Build ISO by default
all: Makefile iso

include make/compile.mk
include make/iso.mk
include make/emulation.mk

# Aliases
kernel: $(KERNEL)
iso: $(ISO)

# Utility targets

clean:
	rm -f $(CXXOBJECTS)
	rm -f $(ASMOBJECTS)
	rm -f $(CXXDEPFILES)
	rm -f $(KERNEL)
	rm -f $(ISO)
	rm -rf iso/

.PHONY: all iso kernel qemu qemu-kernel clean
