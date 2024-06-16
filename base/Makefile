FILES := $(shell find . -type f -not -name "Makefile")

SYSROOT_FILES := $(FILES:%=$(SYSROOT_DIR)/%)

.PHONY: install
install: $(SYSROOT_FILES)

$(SYSROOT_FILES): $(FILES)
	@mkdir -p $(@D)
	@printf "  INSTALL $(notdir $@)\n"
	@install $< $@
