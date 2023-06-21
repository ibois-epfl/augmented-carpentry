#!/bin/bash

sudo apt-get update
sudo apt-get install qtbase5-dev libqt5opengl5-dev libopenni2-dev

cd ./deps/TTool

if [ -d build ]; then
    rm -rf build/*
fi
./configure.sh
./build.sh

cd build
sudo make install