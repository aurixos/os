include config.mk

.PHONY: all
all: $(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE)
	@$(MAKE) -C limine

.PHONY: install
install: all
	@mkdir -p $(SYSROOT_DIR)/boot
	@printf "  INSTALL limine.cfg\n"
	@install limine.cfg $(SYSROOT_DIR)/boot/limine.cfg

$(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  INSTALL $(notdir $@)\n"
	@install limine/BOOTX64.EFI $@
