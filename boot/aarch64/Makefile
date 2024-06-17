.PHONY: all
all:
	@:

install: bootcode.bin fixup.dat start.elf
	@mkdir -p $(SYSROOT_DIR)
	@printf "  INSTALL config.txt\n"
	@install config.txt $(SYSROOT_DIR)

bootcode.bin:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/bootcode.bin -O bootcode.bin 2>/dev/null &>1

fixup.dat:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/fixup.dat -O fixup.dat 2>/dev/null &>1

start.elf:
	@printf "  WGET $@"
	@wget https://github.com/raspberrypi/firmware/raw/stable/boot/start.elf -O start.elf 2>/dev/null &>1
