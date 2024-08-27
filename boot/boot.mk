###################################################################################
## Module Name:  boot.mk                                                         ##
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

INCLUDE_DIRS += include/arch/$(ARCH)

export BOOT_AS := $(ARCH)-elf-gcc
export BOOT_CC := $(ARCH)-elf-gcc
export BOOT_LD := $(ARCH)-elf-ld

# HACK: Temporary fix
export BOOT_ASFLAGS := $(foreach d, $(INCLUDE_DIRS), -I$d)
#export BOOT_ASFLAGS := $(ASFLAGS) $(foreach d, $(INCLUDE_DIRS), -I$d)
export BOOT_CFLAGS := $(CFLAGS)
export BOOT_LDFLAGS := $(LDFLAGS)

export BOOT_ASFILES := $(shell find arch/$(ARCH) -name '*.S' -type f -not -path "arch/$(ARCH)/uefi")
export BOOT_CFILES := $(shell find arch/$(ARCH) -name '*.c' -type f -not -path "arch/$(ARCH)/uefi")

export BOOT_OBJ := $(BOOT_CFILES:%.c=$(BUILD_DIR)/boot/boot/%.c.o) \
					$(BOOT_ASFILES:%.S=$(BUILD_DIR)/boot/boot/%.S.o) \
					$(COMMON_CFILES:common/%.c=$(BUILD_DIR)/boot/boot/common/%.c.o)

include arch/$(ARCH)/boot.mk
