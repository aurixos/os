# No matter where the makefile is run, this should always be equal to the root
# of this repo.
export ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

export ARCH ?= x86_64
export MACH ?= pc
export DEBUG ?= yes

export BUILD_DIR := $(ROOT_DIR)/build
export RELEASE_DIR := $(ROOT_DIR)/release
export SYSROOT_DIR := $(ROOT_DIR)/sysroot

export GIT_REV := $(shell git rev-parse --short HEAD)

LIVE_ISO := $(RELEASE_DIR)/aurixos-livecd-$(GIT_REV)_$(ARCH)-$(MACH).iso
LIVE_HDD := $(RELEASE_DIR)/aurixos-liveusb-$(GIT_REV)_$(ARCH)-$(MACH).img

export AURIXOS_VERSION := $(GIT_REV)

export AURIXOS_ARCH := $(ARCH)
ifeq ($(DEBUG),yes)
export AURIXOS_CONFIGURATION := Debug
else
export AURIXOS_CONFIGURATION := Release
endif

# User-changeable flags
export CFLAGS ?= -O2 -g -Wall -Wextra -DAURIXOS_VERSION=$(AURIXOS_VERSION) -DAURIXOS_ARCH=$(AURIXOS_ARCH) -DAURIXOS_CONFIGURATION=$(AURIXOS_CONFIGURATION) -DAURIXOS_$(ARCH)
export ASFLAGS ?= 
export LDFLAGS ?=

-include arch/$(ARCH)/config.mk
QEMU_FLAGS ?= -m 1G -serial stdio

# Check if architecture is supported
# @todo: this should be better
ifeq ($(ARCH),x86_64)
else ifeq ($(ARCH),aarch64)
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
all: bootloader kernel drivers # Builds the entire OS

.PHONY: liveall
liveall: livehdd livecd # Generates both CD and HDD live images

.PHONY: sysroot
sysroot: all # Builds system root folder structure
	@printf ">>> Building system root...\n"
	@mkdir -p $(SYSROOT_DIR)
	@$(MAKE) -C boot/$(ARCH) install
	@$(MAKE) -C kernel install
	@$(MAKE) -C base install

.PHONY: run
run: #livehdd # Runs QEMU
	@$(QEMU) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -hda $(LIVE_HDD)

# TODO: Maybe add a nice message with instructions here before running qemu?
.PHONY: rundbg
rundbg: livecd # Runs QEMU with a GDB server
	@$(QEMU) $(QEMUGDB) $(QEMU_FLAGS) $(QEMU_ARCH_FLAGS) -cdrom $(LIVE_ISO)

.PHONY: livecd
livecd: $(LIVE_ISO) # Generates a live CD-ROM image

.PHONY: livehdd
livehdd: $(LIVE_HDD) # Generates a live Hard Disk image

.PHONY: bootloader
bootloader: # Builds the bootloader
	@printf ">>> Building bootloader...\n"
	@$(MAKE) -C boot/$(ARCH)

.PHONY: kernel
kernel: # Builds the kernel
	@printf ">>> Building kernel...\n"
	@$(MAKE) -C kernel

.PHONY: drivers
drivers: # Builds all drivers
	@printf ">>> Building drivers...\n"
	@$(MAKE) -C drivers

.PHONY: help
help: # Print help
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	$(SED) "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

$(LIVE_ISO): all sysroot
	@printf ">>> Generating ISO image..."
	@mkdir -p $(RELEASE_DIR)
	@bash arch/$(ARCH)/generate_iso.sh $(LIVE_ISO)

$(LIVE_HDD): all sysroot
	@printf ">>> Generating HDD image..."
	@mkdir -p $(RELEASE_DIR)
	@bash arch/$(ARCH)/generate_hdd.sh $(LIVE_HDD)

.PHONY: clean
clean:
	@rm -rf $(RELEASE_DIR) $(BUILD_DIR) $(SYSROOT_DIR)
