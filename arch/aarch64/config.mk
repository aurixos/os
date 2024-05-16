ifndef ($(BOARD))
override BOARD := raspi3b
$(info Emulation board not specified, defaulting to $(BOARD)...)
endif

include arch/aarch64/$(BOARD)/qemu.mk

QEMU := qemu-system-aarch64
QEMU_ARCH_FLAGS := $(QEMU_BOARD_FLAGS)

ARCH_RELEASE_HDD_RECOMMENDED_SIZE := 0
ARCH_RELEASE_SDCARD_RECOMMENDED_SIZE := 128
