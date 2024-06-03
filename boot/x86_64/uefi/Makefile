include config.mk

ifeq ($(DEBUG),yes)
INTERNAL_CFLAGS += -g -D_DEBUG
endif

CFILES := $(shell find . -type f -name '*.c')

BOOT_OBJS := $(CFILES:%.c=$(BUILD_DIR)/boot/uefi/%.c.o)
HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BOOT_FILE)

.PHONY: install
install:
	@mkdir -p $(SYSROOT_DIR)/EFI/BOOT
	@cp $(BOOT_FILE) $(SYSROOT_DIR)/EFI/BOOT/

-include $(HEADER_DEPS)
$(BUILD_DIR)/boot/uefi/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BOOT_FILE): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
