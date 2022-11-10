# Augmented Carpentry

[<img src="https://github.com/aiekick/ImGuiFileDialog/workflows/Linux/badge.svg"/>](https://github.com/ibois-epfl/augmented-carpentry)

<p>
    <img src="./assets/images/logos/logo_linux_gray_mc.png" width="200">
</p>


AR app is a linux desktop application containing a custom-made framework for augmented carpentry.

## TODOList
> - [ ] Design AC custom 3D file for import of execution 3D models (only points and lines)
> - [x] Add Mapping subprogram + UI
> - [x] Implement padding for 3D scene viewer
> - [x] Test if changing map on the go breaks the slam or not

> - [ ] Write a sub-program to calibrate the camera and export the correct format in xml

> - [ ] Find a way to sync SLAM maps and data
> - [x] Make the Camera of the viewport bigger

> - [ ] Add pop up program to calibrate camera

> - [ ] Add `this->properties` as rule in contributing guide and refactor all the code

> - [x] Make the Camera of the viewport bigger (Defined in `Renderer.cpp:139`)

> - [x] Edit the readme for render API how to use it
> - [x] Refactor the Render part, put everything in one folder and extract/rename render API header.
> - [x] Add a function DrawCircle() to the RenderAPI
> - [x] Add a function DrawCylinder() to the RenderAPI
> - [x] Add a function DrawPolyline() to the RenderAPI
> - [x] Add a function DrawTriangle() to the RenderAPI
> - [x] Add a function DrawText() to the RenderAPI
> - [x] Fix the textRender, which is either not shown or overriding the scene
> - [ ] Cache objects in RenderAPI for speed up (option)

> - [ ] We have to check (or at least catch) the error that may occur due to the incompatible camera parameter and SLAM map after camera calibration.
> - [ ] Undistort Camera view
> - [ ] Bug when selecting path & filename to "save" (can't type)
> - [ ] Make the viewport size a config (now is fixed in the code)

<br />

## Set touch monitor

The prototype is tested on a touch screen 7inch HDMI LCD (B) (WaveShare WS170120) and a laptop running Ubuntu 20/22.04 LTS. To config the touch screen on the pc follow ![these steps first](https://www.waveshare.com/wiki/7inch_HDMI_LCD_(B)). Be sure to switch the display on, plug the mini-USB and finally plug the HDMI cable.

Set the display properties in the `config.ini` properties (to find them run the commands `xinput`  for the name and `xrandr` for the connection type).
```c++
[MonitorSpecs]
monitor_name = WaveShare WS170120
monitor_link_t = HDMI
monitor_resolution = 800x480
```
**You can build AS with the touch screen or on a non-touch screen.** To do so set ON or OFF the CMake option `DEPLOY_ON_TOUCH` in the `CMakeLists.txt`:

<br />

## STag PDFs
Stags are prepared in PDFs batches of ~150 stripes. You can find them [here](https://drive.google.com/drive/folders/1jic85gclymiV9014zc3tuUgIBq8lTyZr?usp=sharing).
They are made to be print as stickers. The code to generate them can be found ![here](https://github.com/ibois-epfl/TSlam/tree/main/stag_util).


<br />


## Build
If it is the first time you are installing AC, set all the dependecies options in the `CMakeLists.txt` file to **ON**.

```bash
    ./configure.sh (or ./configure.sh -c for cleaning out the build folder)
    ./build.sh
```
To run the code:
```bash
./run.sh
```

## How to contribute
Please have a look at the `contributing.md" file. There you will find all the set of rules and the main softwarer documentation to contribute.
