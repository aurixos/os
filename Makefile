export ARCH ?= x86_64
export DEBUG ?= yes

export GIT_REV := $(shell git rev-parse --short HEAD)
export AURIXOS_VERSION := $(GIT_REV)
export AURIXOS_ARCH := $(ARCH)
ifeq ($(DEBUG),yes)
export AURIXOS_CONFIGURATION := Debug
else
export AURIXOS_CONFIGURATION := Release
endif

# No matter where the makefile is run, this should always be equal to the root
# of this repo.
export ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export BUILD_DIR := $(ROOT_DIR)/build
export RELEASE_DIR := $(ROOT_DIR)/release

RELEASE_ISO := $(RELEASE_DIR)/aurixos-cdrom-$(GIT_REV)_$(ARCH).iso
RELEASE_HDD := $(RELEASE_DIR)/aurixos-hdd-$(GIT_REV)_$(ARCH).img
RELEASE_SDCARD := $(RELEASE_DIR)/aurixos-sdcard-$(GIT_REV)_$(ARCH).img

HDD_SIZE ?= $(ARCH_RELEASE_HDD_RECOMMENDED_SIZE)

# User-changeable flags
export CFLAGS ?= -O2 -g -Wall -Wextra -DAURIXOS_VERSION=$(AURIXOS_VERSION) -DAURIXOS_ARCH=$(AURIXOS_ARCH) -DAURIXOS_CONFIGURATION=$(AURIXOS_CONFIGURATION) -DAURIXOS_$(ARCH)
export ASFLAGS ?= 
export LDFLAGS ?=

include arch/$(ARCH)/config.mk
QEMU_FLAGS ?= -m 2G -serial stdio

# Check if architecture is supported
# @todo: this should be better
ifeq ($(ARCH),x86_64)
else ifeq ($(ARCH),aarch64)
$(warning aarch64 building support is not yet complete!)
else
$(error Architecture '$(ARCH)' is not supported.)
endif

UNAME=$(shell uname -s)
ifeq ($(UNAME),Darwin)
	SED=gsed
else
	SED=sed
endif

.PHONY: all
all: bootloader kernel # Builds the entire OS

.PHONY: release_full
release_full: release_hdd release_sdcard release_iso # Generates all possible images

.PHONY: run
run: release_iso # Runs QEMU
	@$(QEMU) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -cdrom $(RELEASE_ISO)

# TODO: Maybe add a nice message with instructions here before running qemu?
.PHONY: rundbg
rundbg: release_iso # Runs QEMU with a GDB server
	@$(QEMU) $(QEMUGDB) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -cdrom $(RELEASE_ISO)

.PHONY: release_iso
release_iso: $(RELEASE_ISO) # Generates a CD-ROM image

.PHONY: release_hdd
release_hdd: $(RELEASE_HDD) # Generates an Hard Disk image

.PHONY: release_sdcard
release_sdcard: $(RELEASE_SDCARD) # Generates an SD Card image

.PHONY: bootloader
bootloader: # Builds the bootloader
	@printf ">>> Building bootloader...\n"
	@$(MAKE) -C boot/$(ARCH)

.PHONY: kernel
kernel: # Builds the kernel
	@printf ">>> Building kernel...\n"
	@$(MAKE) -C kernel

.PHONY: help
help: # Print help
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	$(SED) "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

$(RELEASE_ISO): bootloader kernel
	@printf ">>> Generating ISO image..."
	@mkdir -p $(RELEASE_DIR)
	@bash arch/$(ARCH)/generate_iso.sh $(RELEASE_ISO)

$(RELEASE_HDD): bootloader kernel
	@printf ">>> Generating HDD image..."
	@mkdir -p $(RELEASE_DIR)
	@bash arch/$(ARCH)/generate_hdd.sh $(RELEASE_HDD) $(HDD_SIZE)

$(RELEASE_SDCARD): bootloader kernel
	@printf ">>> Generating SD Card image..."
	$(error SD Card file generation is not supported yet!)
	@mkdir -p $(RELEASE_DIR)
	@bash arch/$(ARCH)/generate_sdcard.sh $(RELEASE_SDCARD)

.PHONY: clean
clean:
	@rm -rf $(RELEASE_DIR) $(BUILD_DIR)
