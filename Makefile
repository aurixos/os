export ARCH ?= x86_64

export ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

export BUILD_DIR ?= $(ROOT_DIR)/build
export SYSROOT_DIR ?= $(ROOT_DIR)/sysroot
export RELEASE_DIR ?= $(ROOT_DIR)/release

export GITREV := $(shell git rev-parse --short HEAD)

LIVECD := $(RELEASE_DIR)/aurix-$(GITREV)-livecd_$(ARCH).iso
LIVEHDD := $(RELEASE_DIR)/aurix-$(GITREV)-livehdd_$(ARCH).img

QEMU_FLAGS := -m 2G -smp 4 #-bios ovmf/ovmf-$(ARCH).fd

.PHONY: boot
boot:
	@printf ">>> Building bootloader...\n"
	@$(MAKE) -C boot boot
	@printf ">>> Building UEFI bootloader...\n"
	@$(MAKE) -C boot uefi

.PHONY: install
install: boot
	@printf ">>> Building sysroot...\n"
	@mkdir -p $(SYSROOT_DIR)
	@$(MAKE) -C boot install

ovmf:
	@printf ">>> Downloading OVMF images...\n"
	@utils/download-ovmf.sh

.PHONY: livecd
livecd: install
	@printf ">>> Generating Live CD..."
	@mkdir -p $(RELEASE_DIR)
	@utils/arch/$(ARCH)/generate-iso.sh $(LIVECD)

.PHONY: livehdd
livehdd: install
	@printf ">>> Generating Live HDD..."
	@mkdir -p $(RELEASE_DIR)
	@utils/arch/$(ARCH)/generate-hdd.sh $(LIVEHDD)

.PHONY: run
run: livecd
	@printf ">>> Running QEMU...\n"
	@qemu-system-$(ARCH) $(QEMU_FLAGS) $(QEMU_MACHINE_FLAGS) -cdrom $(LIVECD)

.PHONY: run-uefi
run-uefi: livecd ovmf
	@printf ">>> Running QEMU (UEFI)...\n"
	@qemu-system-$(ARCH) $(QEMU_FLAGS) $(QEMU_MACHINE_FLAGS) -bios ovmf/ovmf-$(ARCH).fd -cdrom $(LIVECD)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(SYSROOT_DIR)

.PHONY: distclean
distclean:
	@rm -rf $(BUILD_DIR) $(SYSROOT_DIR) $(RELEASE_DIR) ovmf/
