override KERNEL_FILE := System/axkrnl

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

override INTERNAL_LDFLAGS := -nostdlib \
							-flto \
							--no-dynamic-linker \
							-z max-page-size=0x1000 \
							-z text \
							-melf_i386 \
							-static
