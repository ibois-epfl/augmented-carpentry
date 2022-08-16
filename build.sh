#!/bin/bash

is_max_processor_build=true

while getopts ":c" opt; do
    case $opt in
        c)  # make with default number of processors
            is_max_processor_build=false
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done


if $is_max_processor_build ; then
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

