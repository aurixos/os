include config.mk

ifeq ($(DEBUG),yes)
INTERNAL_CFLAGS += -g -D_DEBUG
endif

CFILES := $(shell find s2 -type f -name '*.c')
ASFILES := $(shell find s2 -type f -name '*.asm')

BOOT_OBJS := $(CFILES:%.c=$(BUILD_DIR)/boot/bios/%.c.o) \
			$(ASFILES:%.asm=$(BUILD_DIR)/boot/bios/%.asm.o)

HEADER_DEPS := $(CFILES:.c=.d)

BOOT_FILES_STAGE1 := $(BOOT_FILE_STAGE1_CD) $(BOOT_FILE_STAGE1_HDD) # $(BOOT_FILE_STAGE1_PXE)

.PHONY: all
all: boot_stage1 boot_stage2

.PHONY: install
install: boot_stage2
	@mkdir -p $(SYSROOT_DIR)/System/boot
	@cp $(BOOT_FILES_STAGE1) $(BOOT_FILE_STAGE2) $(SYSROOT_DIR)/System/boot/

.PHONY: boot_stage1
boot_stage1: boot_stage1_cd boot_stage1_hdd # boot_stage1_pxe

.PHONY: boot_stage1_hdd
boot_stage1_hdd: $(BOOT_FILE_STAGE1_HDD)

.PHONY: boot_stage1_cd
boot_stage1_cd: $(BOOT_FILE_STAGE1_CD)

.PHONY: boot_stage1_pxe
boot_stage1_pxe: $(BOOT_FILE_STAGE1_PXE)

.PHONY: boot_stage2
boot_stage2: $(BOOT_FILE_STAGE2)

$(BOOT_FILE_STAGE1_HDD): s1/stage1-hdd.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) -w-zeroing $< -o $@

$(BOOT_FILE_STAGE1_CD): s1/stage1-cd.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) -w-zeroing $< -o $@

$(BOOT_FILE_STAGE1_PXE): s1/stage1-pxe.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) -w-zeroing $< -o $@

-include $(HEADER_DEPS)
$(BUILD_DIR)/boot/bios/%.c.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(INTERNAL_CFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/boot/bios/%.asm.o: %.asm
	@mkdir -p $(@D)
	@printf "  AS $<\n"
	@$(AS) $(INTERNAL_ASFLAGS) $(ASFLAGS) $< -o $@

$(BOOT_FILE_STAGE2): $(BOOT_OBJS)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(LD) $(INTERNAL_LDFLAGS) $(LDFLAGS) $^ -o $@
