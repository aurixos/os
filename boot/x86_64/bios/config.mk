override BOOT_FILE_STAGE1_HDD := $(BUILD_DIR)/boot/axb1-hdd.bin
override BOOT_FILE_STAGE1_CD := $(BUILD_DIR)/boot/axb1-cd.bin
override BOOT_FILE_STAGE1_PXE := $(BUILD_DIR)/boot/axb1-pxe.bin
override BOOT_FILE_STAGE2 := $(BUILD_DIR)/boot/axb2.bin

override INCLUDE_DIRS := include ../../sdk/public

override AS := nasm
override CC := x86_64-elf-gcc
override LD := x86_64-elf-ld

override INTERNAL_CFLAGS := -m64 \
							-ffreestanding \
							-fno-stack-protector \
							-D_AXBOOT \
							$(foreach d, $(INCLUDE_DIRS), -I$d)

override INTERNAL_LDFLAGS := -nostdlib \
							-Tstage2.x
