override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld

override INTERNAL_CFLAGS := -std=c99 \
							-ffreestanding \
							-fPIE \
							-m64 \
							-march=x86-64 \
							-mabi=sysv \
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
