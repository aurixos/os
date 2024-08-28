###################################################################################
## Module Name:  Makefile                                                        ##
## Project:      AurixOS                                                         ##
##                                                                               ##
## Copyright (c) 2024 Jozef Nagy                                                 ##
##                                                                               ##
## This source is subject to the MIT License.                                    ##
## See License.txt in the root of this repository.                               ##
## All other rights reserved.                                                    ##
##                                                                               ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   ##
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        ##
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, ##
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE ##
## SOFTWARE.                                                                     ##
###################################################################################

.DEFAULT_GOAL := all

export ARCH ?= x86_64

export INCLUDE_DIRS := include

export BUILD_DIR ?= build
export SYSROOT_DIR ?= sysroot

export ASFLAGS := 
export CFLAGS := -ffreestanding -mno-red-zone -mno-stack-arg-probe -fno-stack-protector -fno-stack-check -O3 -MMD -MP
export LDFLAGS := -nostdlib

export COMMON_CFILES := $(shell find common -name '*.c')
export COMMON_ARCH_CFILES := $(shell find arch/$(ARCH)/common -name '*.c')
export COMMON_ARCH_ASFILES := $(shell find arch/$(ARCH)/common -name '*.asm')

include boot.mk
include uefi.mk

.PHONY: all
all: boot uefi

.PHONY: boot
boot: $(BOOTFILE)

.PHONY: uefi
uefi: $(UEFI_BOOTFILE)

.PHONY: install
install: boot uefi install-boot install-uefi

clean:
	@rm -rf $(BUILD_DIR) $(SYSROOT_DIR)
