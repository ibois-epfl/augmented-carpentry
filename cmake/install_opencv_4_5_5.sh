#!/bin/bash

sudo apt-get update

sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

# if directory exists, remove it
if [ -d "opencv_build" ]; then
    rm -rf opencv_build
fi
mkdir ~/opencv_build && cd ~/opencv_build

wget https://github.com/opencv/opencv_contrib/archive/refs/tags/4.5.5.zip
unzip 4.5.5.zip
rm 4.5.5.zip
wget https://github.com/opencv/opencv/archive/4.5.5.zip
unzip 4.5.5.zip
rm 4.5.5.zip

cd ~/opencv_build/opencv-4.5.5
mkdir -p build && cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib-4.5.5/modules \
    -D BUILD_EXAMPLES=ON ..

make -j$(nproc)

sudo make install

pkg-config --modversion opencv4
