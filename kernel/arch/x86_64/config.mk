override KERNEL_FILE := System/axkrnl

override AS := nasm
override CC := clang
override LD := clang

override INTERNAL_ASFLAGS := -felf64

override INTERNAL_CFLAGS := -std=c11 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fno-pie \
							-fno-pic \
							-m64 \
							-march=x86-64 \
							-mabi=sysv \
							-mno-80387 \
							-mno-mmx \
							-mno-sse \
							-mno-sse2 \
							-mno-red-zone \
							-mcmodel=kernel \
							-MMD \
							--target=x86_64-elf

override INTERNAL_LDFLAGS := -nostdlib \
							-z max-page-size=4096 \
							-static \
							--target=x86_64-elf