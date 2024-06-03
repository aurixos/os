.PHONY: all
all: bios-cd bios-hdd uefi

.PHONY: bios
bios: bios-cd bios-hdd

.PHONY: bios-cd
bios-cd:
	@$(MAKE) -C bios BOOTLOADER_TYPE=cd

.PHONY: bios-hdd
bios-hdd:
	@$(MAKE) -C bios BOOTLOADER_TYPE=hdd

.PHONY: uefi
uefi:
	@$(MAKE) -C uefi

.PHONY: install
install: bios uefi
	@$(MAKE) -C bios install
	@$(MAKE) -C uefi install
