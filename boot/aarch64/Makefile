include config.mk

ASFILES := $(shell find . -type f -name '*.S')

BOOT_OBJS := $(ASFILES:%.S=$(BUILD_DIR)/%.S.o)

.PHONY: all
all: $(BUILD_DIR)/$(BOOT_FILE)

$(BUILD_DIR)/%.S.o: %.S
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/$(BOOT_FILE): $(BOOT_OBJS)
