override KERNEL_FILE := System/axkrnl

override AS := nasm
override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld

override INTERNAL_ASFLAGS := -felf64

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fno-lto \
							-fpie \
							-m64 \
							-march=x86-64 \
							-mabi=sysv \
							-mno-80387 \
							-mno-mmx \
							-mno-sse \
							-mno-sse2 \
							-mno-red-zone \
							-MMD \
							-MP

override INTERNAL_LDFLAGS := -nostdlib \
							--no-dynamic-linker \
							-z max-page-size=4096 \
							-z text \
							-melf_x86_64 \
							-static \
							-pie
