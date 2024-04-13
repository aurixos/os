#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

disk_name=$1

tempmountdir=$(mktemp -d 2>/dev/null)

mkdir -p $tempmountdir/boot/limine
mkdir -p $tempmountdir/EFI/BOOT
cp -r $ROOT_DIR/build/output/* $tempmountdir/
cp -r $ROOT_DIR/sysroot/* $tempmountdir/
cp $ROOT_DIR/boot/x86_64/limine/limine-bios.sys $ROOT_DIR/boot/x86_64/limine/limine-bios-cd.bin $ROOT_DIR/boot/x86_64/limine/limine-uefi-cd.bin $tempmountdir/boot/limine
cp $ROOT_DIR/boot/x86_64/limine/BOOTX64.EFI $tempmountdir/EFI/BOOT/
xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot boot/limine/limine-uefi-cd.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	$tempmountdir -o $1 >/dev/null 2>&1
$ROOT_DIR/boot/x86_64/limine/limine bios-install $1 >/dev/null 2>&1

rm -rf $tempmountdir

printf " done.\n"
