QEMU := qemu-system-x86_64
QEMU_ARCH_FLAGS := -M q35 -bios arch/$(ARCH)/ovmf_x64.fd
