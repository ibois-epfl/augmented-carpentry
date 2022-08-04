#!/bin/bash

if [ -d build ]; then
    # cmake --build build
    make -j$(nproc) -C build
else
    echo "[ERROR] The build output dir does not exist. Run configure.sh first."
    exit 1
fi