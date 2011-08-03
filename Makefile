# Build ISO by default
all: Makefile iso

include make/compile.mk
include make/iso.mk

# Aliases
kernel: $(KERNEL)
iso: $(ISO)

# Utility targets

QEMUFLAGS = -serial stdio -soundhw pcspk

qemu: iso
	qemu $(QEMUFLAGS) -cdrom $(ISO)

qemu-kernel: kernel
	qemu $(QEMUFLAGS) -kernel $(KERNEL)

clean:
	rm -f $(CXXOBJECTS)
	rm -f $(ASMOBJECTS)
	rm -f $(CXXDEPFILES)
	rm -f $(KERNEL)
	rm -f $(ISO)
	rm -rf iso/

.PHONY: all iso kernel clean
