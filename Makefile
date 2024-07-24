export ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

export BUILD_DIR ?= $(ROOT_DIR)/build
export SYSROOT_DIR ?= $(ROOT_DIR)/sysroot
export RELEASE_DIR ?= $(ROOT_DIR)/release

.PHONY: boot
boot:
	@printf ">>> Building bootloader...\n"
	@$(MAKE) -C boot boot
	@printf ">>> Building UEFI bootloader...\n"
	@$(MAKE) -C boot uefi

.PHONY: install
install:
	@printf ">>> Building sysroot...\n"
	@mkdir -p $(SYSROOT_DIR)
	@$(MAKE) -C boot install

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(SYSROOT_DIR)

.PHONY: distclean
distclean:
	@rm -rf $(BUILD_DIR) $(SYSROOT_DIR) $(RELEASE_DIR)
