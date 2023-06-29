# Augmented Carpentry

<p>
    <img src="./assets/images/logos/logo_linux_gray_mc.png" width="200">
</p>


AR app is a linux desktop application containing a custom-made framework for augmented carpentry.

## TODOList
> - [ ] when we create the output yaml map we should not the calibration file and/or the camera model since this files is calibration-dependent
> - [ ] create find package for TSlam instead install it locally
> - [ ] for the reporitories we roked in IBOIS for the gitsubmodules, be sure that nobody can do modifications

> - [ ] Design AC custom 3D file for import of execution 3D models (only points and lines)
> - [x] Add Mapping subprogram + UI
> - [x] Implement padding for 3D scene viewer
> - [x] Test if changing map on the go breaks the slam or not

> - [ ] (*important*) vanilla tslam runs way smoother. We might have bottleneck in the AC software since we bleed frames. We should set a profiler and see where we can optimize.

> - [ ] create find package for TSlam instead install it locally
> - [ ] for the reporitories we roked in IBOIS for the gitsubmodules, be sure that nobody can do modifications

> - [ ] Design AC custom 3D file for import of execution 3D models (only points and lines)

[//]: # (> - [x] Add Mapping subprogram + UI)
[//]: # (> - [x] Implement padding for 3D scene viewer)
[//]: # (> - [x] Test if changing map on the go breaks the slam or not)

[//]: # (> - [x] Write a sub-program to calibrate the camera and export the correct format in xml)

> - [ ] Find a way to sync SLAM maps and data

[//]: # (> - [x] Make the Camera of the viewport bigger)

[//]: # (> - [x] Add pop up program to calibrate camera)

> - [ ] Double check if `Dloader.h` is working somewhere or need refactoring/suppression

> - [ ] Double check if `Dloader.h` is working somewhere or need refactoring/suppression

> - [ ] Add `this->properties` as rule in contributing guide and refactor all the code

[//]: # (> - [x] Make the Camera of the viewport bigger &#40;Defined in `Renderer.cpp:139`&#41;)

[//]: # (> - [x] Edit the readme for render API how to use it)
[//]: # (> - [x] Refactor the Render part, put everything in one folder and extract/rename render API header.)
[//]: # (> - [x] Add a function DrawCircle&#40;&#41; to the RenderAPI)
[//]: # (> - [x] Add a function DrawCylinder&#40;&#41; to the RenderAPI)
[//]: # (> - [x] Add a function DrawPolyline&#40;&#41; to the RenderAPI)
[//]: # (> - [x] Add a function DrawTriangle&#40;&#41; to the RenderAPI)
[//]: # (> - [x] Add a function DrawText&#40;&#41; to the RenderAPI)
[//]: # (> - [x] Fix the textRender, which is either not shown or overriding the scene)
> - [ ] Cache objects in RenderAPI for speed up (option)

[//]: # (> - [x] We have to check &#40;or at least catch&#41; the error that may occur due to the incompatible camera parameter and SLAM map after camera calibration.)
[//]: # (> - [x] Undistort Camera view)
> - [ ] Bug when selecting path & filename to "save" (can't type)
> - [ ] Make the viewport size a config (now is fixed in the code)

> - [ ] Load Mesh from UI

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
Cloning the repo with submodules
```bash
git clone --recursive git@github.com:ibois-epfl/augmented-carpentry.git
```
or
```bash
git clone git@github.com:ibois-epfl/TSlam.git
git submodule sync
git pull --recurse-submodules
```

If it is the first time you are installing AC, set all the dependecies options in the `CMakeLists.txt` file to **ON**.

```bash
    ./cmake/install_TSlam.sh (Although CMakeList.txt run this when INSTALL_TSLAM option is on, you might need to install TSlam with this command manually as its need sudo priviledge)
    ./cmake/install_TTool.sh
    ./configure.sh (or ./configure.sh -c for cleaning out the build folder)
    ./build.sh
```
To run the code:
```bash
./run.sh
```

## How to contribute
Please have a look at the `contributing.md" file. There you will find all the set of rules and the main softwarer documentation to contribute.

## 🚧🚧🚧 Memory Leak Issue 🚧🚧🚧
We notice the memory leak caused by TTool integration.
### Cause
- TTool uses Qt5's View to render the track the toolheads.
- AC uses glfw to show window UI.
- Thus, context switching between TTool and AC is required in order for OpenGL to render to the correct buffers.
#### Context Switching
- In order to do the context switching between AC and TTool, we introduced `TTool::MakeCurrent()` and `TTool::ReleaseCurrent()` on TTool.
- We also introduct `Window::MakeCurrent()` and `Window::ReleaseCurrent()` on Window.
- Now, one context needs to be released, before the other can make current.
#### Issues/Behaviours
- We found that the MakeCurrent and ReleaseCurrent cannot be called carelessly.
- In the `Application::Run()`, this make and release will be called repeatedly, which leads to additional memory increase on the program which will not decrease.
#### Replication
- Run this program on this commit, and monitor the memory increase.
- To replicate the worse memory leak rate that we discovered, please change from this commit (d876108cd9cff82dd72c2a1d8be1306c7db3b19a)
```cpp
// Application.cpp

void Application::Run()
{
    // ... code before ...
        m_Window->MakeCurrent(); // ADD THIS LINE

        GetLayer<AIAC::LayerUI>()->OnUIRender();

        m_Window->ReleaseCurrent(); // ADD THIS LINE
    // ... code after ...
    }
}
```
#### Mitigation
- We put the context switching only on the TTool `OnAttach` and `OnFrameStart`.
- In this current commit (d876108cd9cff82dd72c2a1d8be1306c7db3b19a), we found the most bearable memory increase rate, that will allow the program to run for some hours on 10GB memory device.
