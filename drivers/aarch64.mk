override CC := aarch64-elf-gcc
override LD := aarch64-elf-ld

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-nostdlib \
							-nostartfiles

override INTERNAL_LDFLAGS := -nostdlib \
							 -z nostartfiles
