FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive # ignore user input required

RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git
RUN apt-get install -y apt-utils

# install tslam deps
RUN apt-get -y install libopencv-dev
RUN apt-get -y install libgmp-dev libgmp-dev
RUN apt-get -y install libmpfr-dev
RUN apt-get -y install libeigen3-dev
RUN apt-get -y install libboost-all-dev

# install required dependencies for TTool
RUN apt-get -y install libopencv-dev
RUN apt-get -y install libassimp-dev
RUN apt-get -y install libgoogle-glog-dev
RUN apt-get -y install freeglut3-dev libglew-dev libglfw3 libglfw3-dev

# For extracting the libtorch zip
RUN apt-get -y install unzip

# For downloading the dataset
RUN apt-get install -y python3
RUN  apt-get update \
  && apt-get install -y wget \
  && rm -rf /var/lib/apt/lists/*

COPY . .
WORKDIR .


# Clear CMakeCache for Docker (this line is mainly for VSCode dev container)
RUN find . -name "CMakeCache.txt" -type f -delete

# Install TTool
WORKDIR /deps/TTool
# RUN cmake -S . -B build
# RUN cmake --build build --target TTool
# WORKDIR /deps/TTool/build
# RUN make install

# Install TSlam
WORKDIR /deps/TSlam
# RUN cmake -S . -B build
# RUN cmake --build build
# WORKDIR /deps/TSlam/build
# RUN make install

WORKDIR /

# Config/build cmake 
RUN cmake -S . -B build
RUN cmake --build build --target AC