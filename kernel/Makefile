include arch/$(ARCH)/config.mk

ifeq ($(DEBUG),yes)
override INTERNAL_CFLAGS += -g -D_DEBUG
endif

KERNEL_FILE := $(BUILD_DIR)/axkrnl

INCLUDE_DIRS := include include/arch/$(ARCH) libc

override INTERNAL_ASFLAGS += $(foreach d, $(INCLUDE_DIRS), -I$d)
override INTERNAL_CFLAGS += $(foreach d, $(INCLUDE_DIRS), -I$d)

ARCH_CFILES := $(shell find arch/$(ARCH) -type f -name '*.c')
ARCH_ASFILES := $(shell find arch/$(ARCH) -type f -name '*.asm')

CFILES := $(shell find . -type f -name '*.c' -not -path "./arch/*")
ASFILES := $(shell find . -type f -name '*.asm' -not -path "./arch/*")

KERNEL_OBJS := $(ARCH_CFILES:%.c=$(BUILD_DIR)/%.c.o) $(CFILES:%.c=$(BUILD_DIR)/%.c.o) \
				$(ARCH_ASFILES:%.asm=$(BUILD_DIR)/%.asm.o) $(ASFILES:%.asm=$(BUILD_DIR)/%.asm.o)

HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(KERNEL_FILE)

.PHONY: install
install: $(KERNEL_FILE)
	@mkdir -p $(SYSROOT_DIR)/System
	@printf "  INSTALL $(notdir $(KERNEL_FILE))\n"
	@cp $(KERNEL_FILE) $(SYSROOT_DIR)/System/

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.asm.o: %.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(KERNEL_FILE): $(KERNEL_OBJS)
	@mkdir -p $(@D)
ifeq ($(ARCH),aarch64)
	@$(LD) -T$(ROOT_DIR)/kernel/arch/$(ARCH)/linker.x $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $(BUILD_DIR)/kernel8.elf
	@printf "  LD kernel8.elf\n"
	@$(OBJCOPY) -O binary $(BUILD_DIR)/kernel8.elf $@
	@printf "  OBJCOPY $(notdir $@)\n"
else
	@printf "  LD $(notdir $@)\n"
	@$(LD) -T$(ROOT_DIR)/kernel/arch/$(ARCH)/linker.x $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
endif
