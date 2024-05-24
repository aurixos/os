override BOOT_FILE := biosboot.bin

override AS := nasm
override CC := i686-elf-gcc
override LD := i686-elf-ld

override INTERNAL_ASFLAGS := -felf32

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fno-omit-frame-pointer \
							-fno-builtin \
							-fno-pie \
							-m32 \
							-march=i686 \
							-mno-80387 \
							-mno-mmx \
							-mno-sse \
							-mno-sse2 \
							-mno-red-zone \
							-mgeneral-regs-only \
							-MMD \
							-MP

override INTERNAL_LDFLAGS := -melf_i386 \
							 -Obinary\
							 -static
