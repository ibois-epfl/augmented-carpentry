#!/bin/bash

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