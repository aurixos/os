-include ../config.mk

ARMSTUB := $(BUILD_DIR)/armstub.bin

.PHONY: all
all: $(ARMSTUB)

.PHONY: install
install: $(ARMSTUB)
	@mkdir -p $(SYSROOT_DIR)
	@printf "  INSTALL $(notdir $(ARMSTUB))\n"
	@cp $(ARMSTUB) $(SYSROOT_DIR)

$(ARMSTUB): armstub.S
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(CC) $(CFLAGS) -MMD -c $< -o $(BUILD_DIR)/armstub.S.o
	@printf "  LD armstub.elf\n"
	@$(LD) --section-start=.text=0 $(BUILD_DIR)/armstub.S.o -o $(BUILD_DIR)/armstub.elf
	@printf "  OBJCOPY armstub.bin\n"
	@$(OBJCOPY) $(BUILD_DIR)/armstub.elf -O binary $@
