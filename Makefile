# Build ISO by default
all: Makefile iso

include make/compile.mk
include make/iso.mk

# Aliases
kernel: $(KERNEL)
iso: $(ISO)

# Utility targets

clean:
	rm -f $(COBJECTS)
	rm -f $(AOBJECTS)
	rm -f $(COBJECTS:%.o=%.d)
	rm -f $(KERNEL)
	rm -f $(ISO)
	rm -rf iso/

.PHONY: all iso kernel clean
