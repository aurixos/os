FILES := $(shell find . -type f -not -name "Makefile" -not -name ".gitignore")

SYSROOT_FILES := $(FILES:%=$(SYSROOT_DIR)/%)

.PHONY: install
install: $(SYSROOT_FILES)

$(SYSROOT_FILES): $(FILES)

$(SYSROOT_DIR)/%: %
	@mkdir -p $(@D)
	@printf "  INSTALL $<\n"
	@cp $< $@
