include $(ARCH)/config.mk

ifeq ($(DEBUG),yes)
override INTERNAL_CFLAGS += -g -D_DEBUG
endif

INCLUDE_DIRS := include include/$(ARCH) libc

override INTERNAL_ASFLAGS += $(foreach d, $(INCLUDE_DIRS), -I$d)
override INTERNAL_CFLAGS += $(foreach d, $(INCLUDE_DIRS), -I$d)

CFILES := $(shell find . -type f -name '*.c')
ASFILES := $(shell find . -type f -name '*.asm')

KERNEL_OBJS := $(CFILES:%.c=$(BUILD_DIR)/%.c.o) $(ASFILES:%.asm=$(BUILD_DIR)/%.asm.o)

HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BUILD_DIR)/output/$(KERNEL_FILE)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.asm.o: %.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/output/$(KERNEL_FILE): $(KERNEL_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) -T$(ROOT_DIR)/kernel/$(ARCH)/linker.x $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
