override KERNEL_FILE := System/axkrnl

override AS := nasm
override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld

override INTERNAL_ASFLAGS := -felf64

override INTERNAL_CFLAGS := -std=c11 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fpie \
							-m64 \
							-mabi=sysv \
							-mno-80387 \
							-mno-mmx \
							-mno-sse \
							-mno-sse2 \
							-mno-red-zone \
							-MMD

override INTERNAL_LDFLAGS := -nostdlib \
							-z max-page-size=4096 \
							-static
