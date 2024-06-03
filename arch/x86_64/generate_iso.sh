#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

disk_name=$1

xorriso -as mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table -b $BUILD_DIR/boot/stage1-cd.bin -e EFI/BOOT/BOOTX64.EFI $SYSROOT_DIR -o $disk_name 2>/dev/null

printf " done.\n"
