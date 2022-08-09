#!/bin/bash

if [ -d build ]; then
    make -j$($(nproc)-1) -C build
else
    echo "[ERROR] The build output dir does not exist. Run configure.sh first."
    exit 1
fi