# Augmented Carpentry

<p>
    <img src="./assets/images/logos/logo_linux_gray_mc.png" width="200">
</p>


AR app is a linux desktop application containing a custom-made framework for augmented carpentry.

---
---
---

# Guli dev

```mermaid
gantt
    dateFormat  YYYY-MM-DD
    title       Guli AC dev
    axisFormat %Y-%m

    Start                                                     :milestone, crit, strt, 2023-08-02, 0d

    section TTool
    1 Eval protocol design                                      :done, cmkprj, 2023-08-14, 6.2w
    2 State-of-art interface eval                               :done, ref, 2023-08-14, 5w
    3 Eval protocol                                             :done, milestone, milttol, 2023-09-26, 0d
    4 TTool packaging                                           :done, packcont, 2023-09-01, 2.5w
    5 (optional) UI design proposal                             :uidesign, after packcont, 0d
    6 AC exporter                                               :done, acexp, 2023-10-02, 1w
    7 design probing plate                                      :active, active, probplt, after acexp, 12d
    8 fabrication of probing plate                              :active, fabplt, after probplt, 1w
    9 Eval campaign                                             :eval, after fabplt, 1.5w
    10 data processing and graphs                               :active, dataaprgr, after eval, 1w
    11 ML docker image (2d per w)                               :mlclass, after probplt, 5w
    Yves's meeting ttool                                        :milestone, crit, after mlclass, 0d

    section AC
    12 point-cloud 3D model evaluation                          :acdev, after mlclass, 9w
    13 integration of mortaise tools                            :acdev, after mlclass, 9w
    Yves's meeting ac                                        :milestone, crit, 2024-01-28, 0d

    End                                                         :milestone, crit, ender, 2024-01-31, 0d
```

This is the current time that should be spent on which tasks weekly **until working package 9-10-11 are done**. The time is in days:

```mermaid
pie showData
    title Guli's weekly dev time
    "11 ML docker image" : 2
    "9 Eval campaign - 10 graph" : 4
```
Prepare a stand-up with minimum documents of your advancements **every Monday** to discuss during our weekly meeting. The deadlines are the ones indicated in the following descriptions of working packages.
Working packages' goals, deliverables and deadlines are the following:

- **9 Eval campaign**:
    - **Goal**: Evaluate the TTool. The user evaluation in TTool is reported to the evaluation of AC, it will not be present in TTool. The TTool will be only evaluated on the pose accuracy with the probing plate and only one person. Only the ML version will be evaluated and tests are repeated *30 times* for all tools. The goal is to collect data about the pose's accuracy as described in the protocol.
    - **Deliverables**: 
        - **9.1** - **Exported eval data**: Perform physically TTool on all tools as in the protocol and export the data with the AC exporter for each tools 30 times as an exported `.txt` log files (as developed in AC exporter).
        - **9.2** - **Video recording of each cycle**: video recording of AC for each cycle during the evaluation. Total of 30 videos (one for each cycle) need to be saved and stored in IBois server.
    - **Deadline**: 2023-11-10th 🎯

- **10 data processing and graphs**:
    - **Goal**: Process the data collected in the previous working package, store it properly in `.csv` files, create box plot graphs for each tool and export LaTex tables of main evaluation benchmark (e.g. min, max, std, mean, median). The entire evaluation should be done in `TTool/eval`, please organize a sub-folder structure and python project as the one in [TSlam](https://github.com/ibois-epfl/TSlam/tree/main/eval)
    - **Deliverables**: 
        - **10.1** - **Processed data**: All the processed data in `.csv` files format and stored in the `TTool/eval` folder. The csv should contains all the data divided by number of session and at the beginning it should present a summary of the data (e.g. min, max, std, mean, median).
        - **10.2** - **Box plot graphs**: One box plot graph of all tools for the position ([example](https://github.com/ibois-epfl/TSlam/blob/main/eval/img/boxplot_position_graph(2).png)) + one box plot graph of all tools for the orientation ([example](https://github.com/ibois-epfl/TSlam/blob/main/eval/img/boxplot_rotation_graph(2).png)). The graphs should be stored in the `TTool/eval` folder and should be have the same style as TSlam as shown in the example images. As an hint check out the python code I used to generate them, [here](https://github.com/ibois-epfl/TSlam/blob/c2a7a65b9ad44018487afb30074c758e83317fcb/eval/script/visuals.py#L271).
        - **10.3** - **LaTex tables**: LaTex tables presenting the summary of deliverable 10.1 (e.g. min, max, std, mean, median). Also this deliverable should be stored in the `TTool/eval` folder.
        - **10.4** - **Basic documentation of data processing**: a README file in `TTool/eval` that explains how to reproduce the scripts for the analysis and the data visualization.
    - **Deadline**: 2023-11-23rd 🎯

- **11 ML docker image**:
    - **Goal**: Create a docker image of the classifier for ttool that is able to store, organize and train the model based on a select set of tools. The docker image's <u>target is our IBOIS fix station</u>, this image and its API should run only on that machine. Note that the web ui and integration into server <u>are not part of this package and will not be developed before February 2024</u>. All the code should be developed and stored in sub-folder of the `TTool` repository.
    - **Deliverables**:
        - **11.1** - **Collecting new images for the dataset**: retake videos of each tools that we are currently using (the totality at our disposal and with a corresponding 3d model) under multiple light conditions and with different backgrounds. Store the video in the IBOIS server and the IBOIS fix station. Videos should be taken with the camera and free hand but always within the area of where the camera would be mounted in normal AC conditions.
        - **11.2** - **Docker image and API**: with Florian develop a microservice image that could run on the IBOIS pc. The image should be able to store, organize and train the model based on a select set of tools.
        - **11.3** - **Extensive Documentation**: extensive README file that explains how to use the docker image and the API and a **brief** explanation of how the image works.
    - **Deadline**: 2023-12-01st 🎯

---
---
---

## TODOList
> - [ ] the change of the calibration file brakes the tslam (but not the ttool it seems)
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

> - [ ] VideoRecorder: Implement handling for starting a new video while the previous one is still in the processing phase.
> - [ ] VideoRecorder: Button color for pressed and unpressed states.
> - [ ] VideoRecorder: Reduce video file size.

## Set touch monitor

The prototype is tested on a touch screen 7inch HDMI LCD (B) (WaveShare WS170120) and a laptop running Ubuntu 20/22.04 LTS. To config the touch screen on the pc follow [these steps first](https://www.waveshare.com/wiki/7inch_HDMI_LCD). Be sure to switch the display on, plug the mini-USB and finally plug the HDMI cable.

Set the display properties in the `config.ini` properties (to find them run the commands `xinput`  for the name and `xrandr` for the connection type).

The following specs works on the X11 display server. If you are using wayland and wanting to switch to X11 follow [this link](https://helpdesk.psionline.com/hc/en-gb/articles/13470827149332-How-to-perform-the-switch-from-the-Wayland-display-server-to-Xorg-X11-on-Linux-Ubuntu-22-04-LTS)
./
```c++
[MonitorSpecs]
monitor_name = WaveShare WS170120
monitor_link_t = HDMI
monitor_resolution = 800x480
```
For wayland display server. WARNING: Wayland display and touchscreen are not compatible yet as the touchscreen register for the main display and not the small display.
```c++
[MonitorSpecs]
LinkMode = XWAYLAND1
Name = Virtual core pointer
Resolution = 800x480
```
**You can build AS with the touch screen or on a non-touch screen.** To do so set ON or OFF the CMake option `DEPLOY_ON_TOUCH` in the `CMakeLists.txt`:

<br />

## STag PDFs
Stags are prepared in PDFs batches of ~150 stripes. You can find them [here](https://drive.google.com/drive/folders/1jic85gclymiV9014zc3tuUgIBq8lTyZr?usp=sharing).
They are made to be print as stickers. The code to generate them can be found ![here](https://github.com/ibois-epfl/TSlam/tree/main/stag_util).


<br />


## System dependecies
AC needs some local libraries already installed before compilation with cmake. 

Before start you will need many dependencies but the largest will be opencv `4.5.5`. Be sure to have installed this version in your local system.

Next we need glm dependencies and libraries:
```bash
sudo apt-get -y install libmpfr-dev libboost-dev libgoogle-glog-dev \
                        freeglut3-dev libglew-dev libglfw3 libglfw3-dev \
                        git-lfs libassimp-dev libglm-dev libimgui-dev
```

For tbb and opencv you will also need these:
```bash
sudo apt -y install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev 
```
For the video recorder you will need opencv too and ffmpeg
```bash
sudo apt -y install ffmpeg
```

```bash
## Build & run
Cloning the repo with submodules
```bash
git clone --recursive git@github.com:ibois-epfl/augmented-carpentry.git
```
or
```bash
git clone git@github.com:ibois-epfl/augmented-carpentry.git
git submodule sync
git pull --recurse-submodules
```

Next you need to pull the PyTorch dependency with the Large File System in git, to do this:
```bash
cd deps/TTool
git lfs pull
```

Time to build.. If you are deploying on a touch monitor set the flag `-DDEPLOY_ON_TOUCH=ON`, you can config:

```bash
cd augmented-carpentry
cmake -S . -B build
cmake --build build
```

To run the code:
```bash
./build/bin/AC
```

## How to contribute
Please have a look at the `contributing.md" file. There you will find all the set of rules and the main softwarer documentation to contribute.
