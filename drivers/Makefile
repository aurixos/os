SUBDIRS := $(wildcard */.)

export DRIVER_CFLAGS := $(INTERNAL_CFLAGS) $(CFLAGS)
export DRIVER_ASFLAGS := $(INTERNAL_ASFLAGS) $(ASFLAGS)
export DRIVER_LDFLAGS := -T../drivers.ld $(INTERNAL_LDFLAGS) $(LDFLAGS)

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	@mkdir -p $(BUILD_DIR)/drivers/$@
	@$(MAKE) -C $@
