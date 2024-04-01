#!/bin/bash

if [[ -z $1 ]]; then
	printf "Please don't invoke this script manually. Run \`make release_hdd\` instead.\n"
	exit 1
fi

tempwdir=$(mktemp -d 2>/dev/null || mktemp -d -t 'aurix')
pushd $tempwdir >/dev/null 2>&1

# TODO: Make a more robust generation script
dd if=/dev/zero of=$1 bs=1k count=1440 2>/dev/null
mformat -i $1 ::
mcopy -s -i $1 $BUILD_DIR/output/* $ROOT_DIR/sysroot/* ::

printf " done.\n"

popd >/dev/null 2>&1
rm -r $tempwdir