override BOOT_FILE := start.o

override AS := aarch64-elf-gcc

override INTERNAL_ASFLAGS := $(CFLAGS) \
							 -ffreestanding \
							 -nostdinc \
							 -nostdlib \
							 -nostartfiles
