override KERNEL_FILE := $(BUILD_DIR)/kernel8.img

override AS := aarch64-elf-as
override CC := aarch64-elf-gcc
override LD := aarch64-elf-ld

override INTERNAL_ASFLAGS := $(CFLAGS) \
							 -ffreestanding \
							 -nostdlib \
							 -nostartfiles

override INTERNAL_CFLAGS := -std=c99 \
							$(INTERNAL_ASFLAGS)

override INTERNAL_LDFLAGS := -nostdlib \
							 -z nostartfiles
