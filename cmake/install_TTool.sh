#!/bin/bash

sudo apt-get update
sudo apt-get -y install libopencv-dev
sudo apt-get -y install libassimp-dev
sudo apt-get -y install libgoogle-glog-dev
sudo apt-get -y install freeglut3-dev libglew-dev libglfw3 libglfw3-dev

cd ./deps/TTool

if [ -d build ]; then
    rm -rf build/*
fi
./configure.sh
./build.sh

cd build
sudo make install