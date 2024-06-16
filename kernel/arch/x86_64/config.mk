override AS := x86_64-elf-gcc
override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld
override OBJCOPY := aarch64-elf-objcopy

override INTERNAL_ASFLAGS := $(CFLAGS)

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-fno-stack-protector \
							-fno-stack-check \
							-fno-omit-frame-pointer \
							-fno-lto \
							-fPIE \
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
							-flto \
							--no-dynamic-linker \
							-z max-page-size=0x1000 \
							-z text \
							-melf_x86_64 \
							-static \
							-pie
