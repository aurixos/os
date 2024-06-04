override BOOT_FILE := $(BUILD_DIR)/boot/BOOTX64.EFI

override INCLUDE_DIRS := libefi include ../../../sdk/public

override CC := clang
override LD := clang

override INTERNAL_CFLAGS := -target x86_64-unknown-windows \
							-fshort-wchar \
							-D_AXBOOT \
							$(foreach d, $(INCLUDE_DIRS), -I$d)

override INTERNAL_LDFLAGS := -target x86_64-unknown-windows \
							-nostdlib \
							-fuse-ld=lld-link \
							-Wl,-subsystem:efi_application \
							-Wl,-entry:AxBootEntry
