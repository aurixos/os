include config.mk

.PHONY: all
all: $(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE)
	@$(MAKE) -C limine

$(BUILD_DIR)/output/EFI/BOOT/$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  CP $(notdir $@)\n"
	@cp limine/BOOTX64.EFI $@
