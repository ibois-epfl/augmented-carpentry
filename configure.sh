#!/bin/bash

if [ -d build ]; then
    echo "[INFO] build/ dir already present."
else
    mkdir build
fi

while getopts ":c" opt; do
    case $opt in
        c)
            echo "[INFO] Cleaning build/ dir before configure..."
            if [ -d build ]; then
                rm -rf build/*
            fi
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
    esac
done


cmake -S . -B build