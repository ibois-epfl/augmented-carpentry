FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive # ignore user input required

# install required dependencies
# # install required dependencies
RUN apt-get -qq update && apt-get -qq -y install \
    g++ cmake git git-lfs \
    && rm -rf /var/lib/apt/lists/*

# install tslam deps
RUN apt-get -qq update && apt-get -qq -y install \
    freeglut3-dev \
    libfreetype-dev \
    libassimp-dev \
    libboost-all-dev \
    libeigen3-dev \
    libglew-dev \
    libglfw3-dev \
    libglm-dev \
    libgmp-dev \
    libgoogle-glog-dev \
    libmpfr-dev \
    libimgui-dev \
    libopencv-dev=4.5.4+dfsg-9ubuntu4 \
    unzip \
    && rm -rf /var/lib/apt/lists/*
