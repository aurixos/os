#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

disk_name=$1
efi_img=$BUILD_DIR/efi.img

# Create a 1.44MB EFI image
dd if=/dev/zero of=$efi_img bs=1k count=1440 2>/dev/null
mformat -i $efi_img -f 1440 ::
mmd -i $efi_img ::/EFI
mmd -i $efi_img ::/EFI/BOOT
mcopy -i $efi_img $SYSROOT_DIR/EFI/BOOT/BOOTX64.EFI ::/EFI/BOOT
cp $efi_img $SYSROOT_DIR/efi.img

# Create the ISO itself
xorriso -as mkisofs -no-emul-boot -boot-load-size 4 -b System/boot/axb1-cd.bin -c System/boot/bootcat.cat -eltorito-alt-boot -e efi.img $SYSROOT_DIR -o $disk_name 2>/dev/null

printf " done.\n"
