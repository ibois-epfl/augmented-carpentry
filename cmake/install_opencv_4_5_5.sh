#!/bin/bash

# TODO: fix this!
# Install a specific 4.5.5 version needed for the project ac
cd ~
# wget https://github.com/opencv/opencv/archive/4.5.5.zip
wget https://github.com/opencv/opencv_contrib/archive/refs/tags/4.5.5.zip
unzip opencv_contrib-4.5.5.zip
wget https://github.com/opencv/opencv/archive/4.5.5.zip
unzip 4.5.5.zip
cd opencv-4.5.5
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D INSTALL_C_EXAMPLES=OFF \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-4.5.5/modules \
      -D PYTHON_EXECUTABLE=/usr/bin/python3 \
      -D BUILD_EXAMPLES=ON ..
make -j4
sudo make install
sudo ldconfig
python3 -c "import cv2; print(cv2.__version__)"
