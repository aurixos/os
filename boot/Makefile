###################################################################################
## Module Name:  Makefile                                                        ##
## Project:      AurixOS                                                         ##
##                                                                               ##
## Copyright (c) 2024-2025 Jozef Nagy                                            ##
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

export INCLUDE_DIRS := $(BOOT_ROOT)/include

export BUILD_DIR ?= build
export SYSROOT_DIR ?= sysroot

export ASFLAGS := 
export CFLAGS := -D__$(ARCH) -D_AXBOOT -ffreestanding -fno-stack-protector -fno-stack-check -MMD -MP
export LDFLAGS := -nostdlib

export BOOT_ROOT := $(ROOT_DIR)/boot

ifeq ($(DEBUG),yes)
CFLAGS += -O0 -g3
else
CFLAGS += -O2
endif

.PHONY: all
all:
	@$(MAKE) -C platform/$(PLATFORM) all

.PHONY: install
install:
	@$(MAKE) -C platform/$(PLATFORM) install

.PHONY: clean
clean:
	@$(MAKE) -C platform/$(PLATFORM) clean
