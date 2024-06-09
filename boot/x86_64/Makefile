.PHONY: all
all: bios uefi

.PHONY: bios
bios:
	@$(MAKE) -C bios

.PHONY: uefi
uefi:
	@$(MAKE) -C uefi

.PHONY: install
install: bios uefi
	@$(MAKE) -C bios install
	@$(MAKE) -C uefi install
