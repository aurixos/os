override CC := i686-elf-gcc
override LD := i686-elf-ld

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-nostdlib \
							-nostartfiles

override INTERNAL_LDFLAGS := -nostdlib \
							 -z nostartfiles
