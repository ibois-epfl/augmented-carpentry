#!/bin/bash

BUILD_ALL_PROCESSORS = true

while getopts ":c" opt; do
    case $opt in
        c)  # make with default number of processors
            BUILD_ALL_PROCESSORS=false
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done


if [BUILD_ALL_PROCESSORS]; then
    echo "[INFO] Building with make nbr max processors"
    if [ -d build ]; then
        # if nproc smaller than 4
        if [ $(nproc) -lt 6 ]; then
            make -j4 -C build
        else
            make -j$($(nproc)-2) -C build
        fi
    else
        echo "[ERROR] The build output dir does not exist. Run configure.sh first."
        exit 1
    fi
else
    echo "[INFO] Building with make defualt nbr of processor"
    if [ -d build ]; then
        make -C build
    fi
fi

