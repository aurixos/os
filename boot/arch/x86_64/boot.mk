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

BOOT_AS := nasm
BOOT_ASFLAGS += -fbin

# stage 1 bootloader
BOOTFILE := $(BUILD_DIR)/boot/boot/bootsect-hdd.bin
BOOTFILE_CD := $(BUILD_DIR)/boot/boot/bootsect-cd.bin

.PHONY: install-boot
install-boot:
	@

$(BOOTFILE): $(BOOTFILE_CD)
	@mkdir -p $(@D)
	@printf "  AS\tbootsect-hdd.bin\n"
	@$(BOOT_AS) $(BOOT_ASFLAGS) arch/x86_64/boot-hdd.asm -o $@

$(BOOTFILE_CD):
	@mkdir -p $(@D)
	@printf "  AS\tbootsect-cd.bin\n"
	@$(BOOT_AS) $(BOOT_ASFLAGS) arch/x86_64/boot-cd.asm -o $@

#$(BUILD_DIR)/boot/boot/%.c.o: boot/%.c
#	@mkdir -p $(@D)
#	@printf "  CC\t$<\n"
#	@$(BOOT_CC) $(BOOT_CFLAGS) -c $< -o $@
#
#$(BUILD_DIR)/boot/boot/common/%.c.o: common/%.c
#	@mkdir -p $(@D)
#	@printf "  CC\t$<\n"
#	@$(BOOT_CC) $(BOOT_CFLAGS) -c $< -o $@