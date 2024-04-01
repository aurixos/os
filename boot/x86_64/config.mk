override BOOT_FILE := BOOTX64.EFI

override INCLUDE_DIRS := libefi include

override CC := clang
override LD := clang

override INTERNAL_CFLAGS := -target x86_64-unknown-windows \
							$(foreach d, $(INCLUDE_DIRS), -I$d)

override INTERNAL_LDFLAGS := -target x86_64-unknown-windows \
							-nostdlib \
							-fuse-ld=lld-link \
							-Wl,-subsystem:efi_application \
							-Wl,-entry:AxBootEntryPoint
