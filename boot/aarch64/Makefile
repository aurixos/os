include config.mk

.PHONY: all
all: stub

.PHONY: stub
stub:
	@$(MAKE) -C stub

install: stub bootcode.bin fixup.dat start.elf
	@mkdir -p $(SYSROOT_DIR)
	@$(MAKE) -C stub install
	@printf "  INSTALL config.txt\n"
	@cp config.txt $(SYSROOT_DIR)
	@printf "  INSTALL bootcode.bin\n"
	@cp bootcode.bin $(SYSROOT_DIR)
	@printf "  INSTALL fixup.dat\n"
	@cp fixup.dat $(SYSROOT_DIR)
	@printf "  INSTALL start.elf\n"
	@cp start.elf $(SYSROOT_DIR)

bootcode.bin:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/bootcode.bin -O bootcode.bin 2>/dev/null &>1

fixup.dat:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/fixup.dat -O fixup.dat 2>/dev/null &>1

start.elf:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/start.elf -O start.elf 2>/dev/null &>1
