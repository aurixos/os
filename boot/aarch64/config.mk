override AS := aarch64-elf-gcc
override CC := aarch64-elf-gcc
override LD := aarch64-elf-ld
override OBJCOPY := aarch64-elf-objcopy

override INTERNAL_ASFLAGS := $(CFLAGS) \
							 -ffreestanding \
							 -nostdlib \
							 -nostartfiles

override INTERNAL_CFLAGS := -std=c99 \
							$(INTERNAL_ASFLAGS)

override INTERNAL_LDFLAGS := -nostdlib
