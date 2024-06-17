#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

sysroot_size=$(du -hsm kernel | cut -f 1)

disk_name=$1
disk_size=32

unamestr=$(uname)

# Check if we're running on a supported host
if ! [[ "$unamestr" =~ ^('Linux'|'Darwin') ]]; then
	printf " failed. (unsupported host)\n"
	exit 128
fi

# create a disk image
dd if=/dev/zero of="$disk_name" bs=1M count="$disk_size" >/dev/null 2>&1

tempmountdir=$(mktemp -d 2>/dev/null)

# mount disk
if [ "$unamestr" = 'Linux' ]; then
	echo "Linux HDD Generation not implemented yet"
	rm -r $tempmountdir
	exit 200
elif [ "$unamestr" = 'Darwin' ]; then
	loopback=$(hdiutil attach -nomount $disk_name)
	loopback=$(echo $loopback | cut -f1 -d" ")

	loopback_dir="$loopback"s1
fi

# create an MBR partition table
if [ "$unamestr" = 'Linux' ]; then
	fdisk "$loopback" >/dev/null 2>&1 << EOF
n
p
1


b
w
EOF
elif [ "$unamestr" == 'Darwin' ]; then
	fdisk -ie "$loopback" >/dev/null 2>&1 << EOF
y
auto dos
write
quit
EOF
fi

# format EFI partition
mkfs.vfat -F32 -n "AURIXOS" "$loopback_dir" >/dev/null 2>&1

# mount EFI partition
if [ "$unamestr" = 'Darwin' ]; then
	diskutil mount -mountPoint "$tempmountdir" "$loopback_dir" >/dev/null 2>&1
else
	mount "$loopback_dir" "$tempmountdir"
fi

# Copy system root to the newly created image
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

printf " done.\n"

