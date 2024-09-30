#!/usr/bin/env bash

setarch() {
    if [ -z "${1}" ]; then
	echo "Syntax: setarch <arch>"
	return
    fi

    # let's hope everyone has tr
    arch_tmp=$(echo "${1}" | tr '[:upper:]' '[:lower:]')
    case ${arch_tmp} in
	"i686")
	    export build_arch="i686"
	    ;;
	"x86_64")
	    export build_arch="x86_64"
	    ;;
	"aarch64")
	    export build_arch="aarch64"
	    ;;
	"arm" | "arm32")
	    export build_arch="arm"
	    ;;
	"powerpc" | "ppc")
	    export build_arch="ppc"
	    ;;
	*)
	    echo "Unknown architecture. Possible values: i686 | x86_64 | arm (arm32) | aarch64 | powerpc (ppc)"
	    ;;
    esac
}

setmachine() {
        if [ -z "${1}" ]; then
	echo "Syntax: setmachine <machine>"
	return
    fi

    # let's hope everyone has tr
    machine_tmp=$(echo "${1}" | tr '[:upper:]' '[:lower:]')
    case ${machine_tmp} in
	"generic-pc")
	    export build_machine="generic-pc"
	    if [[ ! ${build_arch} =~ ^(i686|x86_64)$ ]]; then
		echo "Invalid architecture '${build_arch}' for machine '${build_machine}' set, defaulting to 'x86_64'..."
		setarch "x86_64"
	    fi
	    ;;
	"rpi3")
	    export build_machine="rpi3"
	    if [[ ! ${build_arch} =~ ^(aarch64)$ ]]; then
		echo "Invalid architecture '${build_arch}' for machine '${build_machine}' set, defaulting to 'aarch64'..."
		setarch "aarch64"
	    fi
	    ;;
	"rpi4")
	    export build_machine="rpi4"
	    if [[ ! ${build_arch} =~ ^(aarch64)$ ]]; then
		echo "Invalid architecture '${build_arch}' for machine '${build_machine}' set, defaulting to 'aarch64'..."
		setarch "aarch64"
	    fi
	    ;;
	"macintosh")
	    export build_machine="macintosh"
	    if [[ ! ${build_arch} =~ ^(ppc)$ ]]; then
		echo "Invalid architecture '${build_arch}' for machine '${build_machine}' set, defaulting to 'powerpc'..."
		setarch "powerpc"
	    fi
	    ;;
	*)
	    echo "Unknown machine. Possible values: generic-pc | rpi3 | rpi4 | macintosh"
	    ;;
    esac
}

setbuild() {
    if [ -z "${1}" ]; then
	echo "Syntax: setbuild <DEBUG | RELEASE>"
	return
    fi

    # let's hope everyone has tr
    build_type_tmp=$(echo "${1}" | tr '[:upper:]' '[:lower:]')
    case ${build_type_tmp} in
	"release")
	    export build_type="RELEASE"
	    ;;
	"debug")
	    export build_type="DEBUG"
	    ;;
	*)
	    echo "Unknown build type. Possible values: DEBUG | RELEASE"
	    ;;
    esac
}

# Default build variables
setarch "x86_64"
setmachine "generic-pc"
setbuild "debug"
