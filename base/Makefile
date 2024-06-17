FILES := $(shell find . -type f -not -name "Makefile" -not -name ".gitignore")

ifeq ($(ARCH),aarch64)
FILES += bootcode.bin \
		fixup.dat \
		start.elf

endif

SYSROOT_FILES := $(FILES:%=$(SYSROOT_DIR)/%)

.PHONY: install
install: $(SYSROOT_FILES)

$(SYSROOT_FILES): $(FILES)
	@mkdir -p $(@D)
	@printf "  INSTALL $(notdir $@)\n"
	@install $< $@

bootcode.bin:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/bootcode.bin -O bootcode.bin 2>/dev/null &>1

fixup.dat:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/fixup.dat -O fixup.dat 2>/dev/null &>1


start.elf:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/start.elf -O start.elf 2>/dev/null &>1


