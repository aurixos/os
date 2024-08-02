#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make livecd\` instead.\n"
	exit 1
fi

disk_name=$1

uefi_image=$BUILD_DIR/uefi.img
tempmountdir=$(mktemp -d 2>/dev/null)

# Create UEFI image
dd if=/dev/zero of=$uefi_image bs=1k count=1440 >/dev/null 2>&1
mformat -i $uefi_image -f 1440 :: >/dev/null 2>&1
mmd -i $uefi_image ::/EFI >/dev/null 2>&1
mmd -i $uefi_image ::/EFI/BOOT >/dev/null 2>&1
mcopy -i $uefi_image $SYSROOT_DIR/EFI/BOOT/BOOTIA32.EFI ::/EFI/BOOT >/dev/null 2>&1
## !FIXME: Huge hack! Make a filesystem.
mmd -i $uefi_image ::/System >/dev/null 2>&1
mcopy -i $uefi_image $SYSROOT_DIR/System/axkrnl ::/System >/dev/null 2>&1

# Create directory structure
mkdir -p $tempmountdir/boot

cp $uefi_image $tempmountdir/boot/uefi.bin
cp $BUILD_DIR/boot/boot/bootsect-cd.bin $tempmountdir/boot/bootcd.bin
cp -r $ROOT_DIR/sysroot/* $tempmountdir/

# Create ISO
xorriso -as mkisofs -b boot/bootcd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot boot/uefi.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	$tempmountdir -o $1 >/dev/null 2>&1

rm -rf $tempmountdir

printf " done.\n"