include config.mk

ASFILES := $(shell find . -type f -name '*.asm')
CFILES := $(shell find . -type f -name '*.c')

BOOT_OBJS := $(ASFILES:%.asm=$(BUILD_DIR)/%.asm.o) \
			 $(CFILES:%.c=$(BUILD_DIR)/%.c.o)

.PHONY: all
all: $(BUILD_DIR)/$(BOOT_FILE)

$(BUILD_DIR)/%.asm.o: %.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	$(LD) $(INTERNAL_LDFLAGS) $(LDFLAGS) $< -o $@
