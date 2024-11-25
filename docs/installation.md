# Getting started

AC *can only be only compiled from source for now* and *runs only on Debian-based systems*. The software is built with *C++* and compiled with *CMake* into an executable. You can either download [the source code](https://github.com/ibois-epfl/augmented-carpentry) and its [GitHub submodules](https://github.blog/open-source/git/working-with-submodules/) like this.

```bash
git clone --recurse-submodules https://github.com/ibois-epfl/augmented-carpentry.git
```

## Dependecies

First refresh the package list and install the necessary dependencies:
```bash
apt-get -qq update && apt-get -qq -y install g++ cmake git git-lfs
```
And here's the system dependecies for the project:
```bash
apt-get -qq update && apt-get -qq -y install \
wget \
curl \
unzip \
xvfb \
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
libopencv-dev
```

The rest of the other dependecies will be automatically downloaded and installed by the CMake build system in the next steps.

## Build and Run

```bash
cd augmented-carpentry
cmake -S . -B build
cmake --build build
```

To run the code be sure that your USB-Camera is connected and run the following command:

```bash
./build/bin/AC
```

!!! Tip
    
    :octicons-file-code-16: [`default_config.ini`](assets/default_config.ini)

    While running the code, make sure that `config.ini` and `assets/` exists in the current directory. If errors related to config present, please reconfigure the `config.ini` by copy-pasting the content from `/assets/default_config.ini`.

That's it your are running Augmented Carpentry🪚!