include ../$(ARCH).mk

DRIVER_NAME := framebuffer
DRIVER := $(DRIVER_NAME).drv

ifeq ($(DEBUG),yes)
override INTERNAL_CFLAGS += -g -D_DEBUG
endif

override INTERNAL_CFLAGS += -I.

CFILES := $(shell find . -type f -name '*.c')

DRIVER_OBJS := $(CFILES:%.c=$(BUILD_DIR)/drivers/$(DRIVER_NAME)/%.c.o)
HEADER_DEPS := $(CFILES:.c=.d)

.PHONY: all
all: $(BUILD_DIR)/output/drivers/$(DRIVER_FILE)

$(BUILD_DIR)/drivers/$(DRIVER_NAME)/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(DRIVER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/output/drivers/$(DRIVER_FILE): $(DRIVER_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) $(DRIVER_LDFLAGS) $^ -o $@
