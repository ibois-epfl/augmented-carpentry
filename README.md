# augmented-carpentry

ARapp is a linux desktop application containing a custom-made framework for augmented carpentry.

## TODOList

> We need an EventSystem, ideally called every frame. Collect the events, dispatch them and solve them seperately. E.g.: when to stop for drilling/cutting or give feedbacks of depth.

## Build
We need a first to install TSlam:

To build the rest:
```bash
    ./configure.sh (or ./configure.sh -c for cleaning out the build folder)
    ./build.sh
```
To run the code:
```bash
./run.sh
```

<br />

## STag PDFs
Stags are prepared in PDFs batches of ~150 stripes. You can find them [here](https://drive.google.com/drive/folders/1jic85gclymiV9014zc3tuUgIBq8lTyZr?usp=sharing).
They are made to be print as stickers. The code to generate them can be found at `TO-BE_DEFINED`.


<br />


## Guide for contributors
Here's you can find some documentations and guidelines to contribute to augmented_carpentry.

### Logging
To log use the following MACROS. All the code is contained in `Log.hpp` and `Log.cpp`. There are two types of logging: one for the *core* (everything related to SLAM or 3D engine, low-level component of the AR engine) and one for *client* (everything on the upper level such as UI, utilities, sockets, web loders, etc.)
```c++
// for core logging
AIAC_CORE_INFO("test_core_info");
AIAC_CORE_WARN("test_core_warn");
AIAC_CORE_CRITICAL("test_core_critical");
AIAC_CORE_DEBUG("test_core_debug");
AIAC_CORE_ERROR("test_core_error");

// for client logging
AIAC_CLI_INFO("test_cli_info");
AIAC_CLI_WARN("test_cli_warn");
AIAC_CLI_CRITICAL("test_cli_critical");
AIAC_CLI_DEBUG("test_cli_debug");
AIAC_CLI_ERROR("test_cli_error");
```
The output is like so:
```bash
[source main.cpp] [function main] [line 32] [16:30:05] CORE: test
```
The logging can be silenced by setting OFF the option in the main `CMakeLists.txt` and do clean reconfiguration.
```cmake
option(SILENT_LOGGING "Do not log messages in the terminal of on." ON)
```