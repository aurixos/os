#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

disk_name=$1
disk_size=$2

minimum_disk_size=12

unamestr=$(uname)

# Check if we're running on a supported host
if ! [[ "$unamestr" =~ ^('Linux'|'Darwin') ]]; then
	printf " failed. (unsupported host)\n"
	exit 128
fi

if [[ $disk_size -lt $minimum_disk_size ]]; then
	printf " failed. (specified disk size is less than minimum)\n"
	printf "Specified size: $disk_size\n"
	printf "Minimum size: $minimum_disk_size\n"
	exit 1
fi

# create a disk image
dd if=/dev/zero of="$disk_name" bs=1M count="$disk_size" >/dev/null 2>&1

# create a partition table
gdisk "$disk_name" >/dev/null 2>&1 << EOF
o
y
n p
1

+128M
ef00
w
y
EOF

tempmountdir=$(mktemp -d 2>/dev/null)

# mount disk
if [ "$unamestr" = 'Linux' ]; then
	echo "Linux HDD Generation not implemented yet"
	rm -r $tempmountdir
	exit 200
elif [ "$unamestr" = 'Darwin' ]; then
	loopback=$(hdiutil attach -nomount $disk_name)
	loopback=$(echo $loopback | cut -f1 -d" ")

	loopback_efi="$loopback"s1
fi

# format EFI partition
mkfs.vfat -F32 -n "EFI" "$loopback_efi" >/dev/null 2>&1

# mount EFI partition
if [ "$unamestr" = 'Darwin' ]; then
	diskutil mount -mountPoint "$tempmountdir" "$loopback_efi" >/dev/null 2>&1
else
	mount "$loopback_efi" "$tempmountdir"
fi

cp -r "$BUILD_DIR"/output/* "$tempmountdir"
cp -r "$ROOT_DIR"/sysroot/* "$tempmountdir"

# unmount all partitions
if [ "$unamestr" = 'Linux' ]; then
	echo "Linux HDD Generation not implemented yet"
	rm -r $tempmountdir
	exit 200
elif [ "$unamestr" = 'Darwin' ]; then
	diskutil unmountDisk "$loopback" >/dev/null 2>&1
fi

rm -r "$tempmountdir"

# copy BIOS bootloader
dd if="$BUILD_DIR/biosboot.bin" of=$disk_name conv=notrunc bs=446 count=1 >/dev/null 2>&1
dd if="$BUILD_DIR/biosboot.bin" of=$disk_name conv=notrunc bs=1 count=2 skip=510 seek=510 >/dev/null 2>&1

printf " done.\n"
