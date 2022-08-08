#!/bin/bash

sudo apt-get update
sudo apt-get install qtbase5-dev libqt5opengl5-dev libopenni2-dev

cd ./deps/TSlam

if [ -d build ]; then
    rm -rf build/*
fi
mkdir build && cd build

cmake -DBUILD_4_API=OFF
make -j$(nproc)
sudo make install