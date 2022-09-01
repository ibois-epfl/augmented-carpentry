# Augmented Carpentry

[<img src="https://github.com/aiekick/ImGuiFileDialog/workflows/Linux/badge.svg"/>](https://github.com/ibois-epfl/augmented-carpentry)

<p>
    <img src="./assets/images/logos/logo_linux_gray_light.png" width="200">
</p>

AR app is a linux desktop application containing a custom-made framework for augmented carpentry.

## TODOList
> - [ ] Design AC custom 3D file for import of execution 3D models (only points and lines)
> - [x] Add Mapping subprogram + UI
> - [x] Implement padding for 3D scene viewer
> - [x] Test if changing map on the go breaks the slam or not

> - [ ] Find a way to sync SLAM maps and data

> - [ ] Add pop up program to calibrate camera

> - [ ] Make the Camera of the viewport bigger

> - [x] Edit the readme for render API how to use it
> - [x] Refactor the Render part, put everything in one folder and extract/rename render API header.
> - [x] Add a function DrawCircle() to the RenderAPI
> - [x] Add a function DrawCylinder() to the RenderAPI
> - [x] Add a function DrawPolyline() to the RenderAPI
> - [x] Add a function DrawTriangle() to the RenderAPI
> - [ ] Add a function DrawText() to the RenderAPI
>   - [ ] Fix the textRender, which is either not shown or overriding the scene
> - [ ] Cache objects in RenderAPI for speed up (option)

Scheme for the last implementation of AC's main structure:
<p>
    <img src="./docs/NextPAC_v1.png" width="600">
</p>



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


## Guide for contributors
Here's you can find some documentations and guidelines to contribute to augmented_carpentry.

### Naming convention
Here's the naming convention for this project:
- `localVariable`: lowerCamelCase.
- `m_PrivateVariable`: Hungarian notation with UpperCamelCase.
- `APP_SPEC`: Constants with SNAKE_UPPER_CASE.
- All the other things uses UpperCamelCase.

Here's an example:
```c++
// next line graph style
void Foo()
{
    /* content */
}

// structure name uses UpperCamelCase
struct AnExampleStruct
{
    // structure attribute uses UpperCamelCase
    const char* Name;
};

// class name uses UpperCamelCase
class AnExampleClass
{
public:
    AnExampleClass(const int& init);
    virtual ~AnExampleClass();

    // member functions use UpperCamelCase
    void PublicMemberFunction()
    {
        // local variable uses lowerCamelCase
        int localVariable = 0;
    }

// A field indicator to separate the functions and attributes
public:
    int PublicVariable;


// Private member function block
private:
    // member functions use UpperCamelCase
    void PrivateMemberFunction(); 

// Also a field indicator to separate the functions and attributes
private:
    // private variables uses Hungarian notation with UpperCamelCase
    int m_PrivateVariable; // m_VariableName for normal variable
    static int s_Instance; // s_VariableName for static variable
};

// Start headers with 
#pragma once

// Start declarations with precompiled headers
#include "aiacpch.h"
```

### Config
We use an [.ini]() file to store the config parameters of the application. The parser is derived from [this project]() but with some modification. Here's an example:
#### Declaration
```cpp
// Just include this header
#include "AIAC/Config.h"

// Open file "config.ini".
// The second param indicate if the file need to be update when 
// InsertEntry() and UpdateEntry() is called.
// The initialization happens in the very beginning of `ACApp.cpp`.
inih::Ini config("config.ini", true);
```

#### Usage
```cpp
AIAC::Config::Get<int>("section", "key1", 10);

// InsertEntry(section, key, value)
AIAC::Config::InsertEntry("section_test", "key1", -1);

// Insert a vector
vector<int> primeVector = {2, 3, 5, 7, 11};
AIAC::Config::InsertEntry("section_test_vector", "prime_number", primeVector);


// Get<T>(section, key, default_value)
// The entry will be created if not exist.
cout << AIAC::Config::Get<int>("section_test", "key1", -1) << endl;
cout << AIAC::Config::Get<string>("section_test", "key2", "I'm a string!") << endl;

// With vector, use GetVector() instead of Get(),
for(auto n: AIAC::Config::GetVector<int>("section_test_vector", "prime_number", primeVector)){
    cout << n << " ";
}
cout << endl;

// Update an Entry
AIAC::Config::UpdateEntry("section_test", "key1", 999);
cout << AIAC::Config::Get("section_test", "key1", -1) << endl;

// For update an vector entry, call the same function as normal
primeVector.push_back(13);
AIAC::Config::UpdateEntry("section_test_vector", "prime_number", primeVector);

// Write the ini to the original file
AIAC::Config::WriteToFile();
// Write to another file
AIAC::Config::WriteToFile("another_config_file.ini");

```
After running thie code above, you gets the following output:
```
-1
I'm a string!
2 3 5 7 11 
999
```
with two identical `.ini` file contains:
```
[section_test]
key1 = 999
key2 = I'm a string!

[section_test_vector]
prime_number = 2 3 5 7 11 13
```
### Pre-Compiled headers
AC uses a precompile header `aiacpch.h` to the project to shorten compilation time for headers that you rarely modify such as stdb library, opencv etc.. Add to `aiacpch.h` every big header you do not use often.
Include at the very top `#include "aiacpch.h"` of every `.cpp` file.

### Layers
Layers are the main component of the framework. Each layer gets stacked and executed in that order. Each layer represents a different unit e.g. TSLAM, camera access, 3Drender, etc. Each layer has events where code can be injected in the loop and custom events.
```c++
namespace AIAC
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        /// Is called when the layer is attached to the application.
        virtual void OnAttach() {}

        /// Is calle before GLFW poll events, GL frame and Imgui Frame
        virtual void OnFrameAwake() {}

        /// Is called when frame starts
        virtual void OnFrameStart() {}

        /// Is called when frame ends
        virtual void OnFrameEnd() {}

        /// Is called when the GLFW, GL and Imgui frame is updated and rendered
        virtual void OnFrameFall() {}

        /// Is called when the layer is detached from the application (~app).
        virtual void OnDetach() {}
    };
}
```

### Getting the main app
There is one only app and it can be accessed from layers with:
```c++
AIAC::Application& app = AIAC::Application::GetInstance();
```
or easier with a macro
```c++
AIAC_APP
```
### Getting other layers' variables
To get other layers' variables use a small query function from the Application class. In the case of accessing test_a of layerA from e.g. layerB:
```c++
AIAC_APP.GetLayer<AIAC::LayerA>()->test_a
```

### UI
UI is mainly built in ImGui. We wrap some of the functions and add custom functionalities.

#### Logos
Logos addresses/data is store in `CustomLogos.h`. As an example:
```c++
#define AIAC_LOGO_LIGHT_GRAY "assets/images/logos/logo_linux_gray_light.png"
```
E.g. to consume it:
```c++
m_LogoBlack = AIAC::Image(AIAC_LOGO_BLACK);
```

#### Colors
Colors macros can be found/add in the header `ClrPalette.h` with the following definition style:
```c++
#define AIAC_UI_DARK_GREY ImVec4(0.2f, 0.2f, 0.2f, 1.0f)
```

#### Panes
For every new layer you can create a new collapsable pannel in the main UI. To do so follow the next steps.

Create a new function (declare it in `LayerUI.h > Class LayerUI` and implement it in `LayerUI.cpp`) and start calling `ImGui` methods from there, put everythin you need for the UI there. This is the only place where you will write UI for your pane, like so:
```c++
void LayerUI::SetPaneUICamera()
    {
        ImGui::Text("This layer is responsible for the physical camera.");
        AIAC::Camera& camera = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera;
        ImGui::Text("Camera is %s", camera.IsOpened() ? "open" : "closed");
        ImGui::Text("Camera resolution: %d x %d", camera.GetWidth(), camera.GetHeight());
    }
```
Next copy past the template function in `LayerUI.cpp` and reference the function you created:
```c++
//                 Label               Collapse              PaneContent
StackPane(PaneUI("Example",              true,       AIAC_BIND_EVENT_FN(SetPaneUIExample)         ));
StackPane(PaneUI("Camera",               true,       AIAC_BIND_EVENT_FN(SetPaneUICamera)          ));
StackPane(PaneUI("Slam",                 true,       AIAC_BIND_EVENT_FN(SetPaneUISlam)            ));
StackPane(PaneUI("<your-new-name>",      true,       AIAC_BIND_EVENT_FN(YourNewContainerMethod)   ));
```

#### File Dialog
The file dialog widget we use is implemented as *singleton* from [this repo](https://github.com/aiekick/ImGuiFileDialog). This means that only one file dialog widget can be opened at once (it is possible to implement it as multiple instance if needed). If you need to select a file from local system, here's the snippet:
```c++
if (ImGui::Button("Open 3dModel"))
            ImGuiFileDialog::Instance()->OpenDialog("Choose3dModel", "Open 3dModel", ".ply, .obj", ".");

        if (ImGuiFileDialog::Instance()->Display("Choose3dModel")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            /* write here what to do with the file path */
            }
            ImGuiFileDialog::Instance()->Close();
        }
```

### Event System
We implement a *bus*-like event system based on the [observer pattern](https://sourcemaking.com/design_patterns/observer/cpp/3) and the [tppevent repo](https://github.com/ibois-epfl/eventpp). It is not *multi-threaded* but it can be modified as such. All the event files are contained in the dir `AIAC/EventSys`.

#### How to raise events
The event *bus* is stored in the Application. You can raise events from other files in two ways, either *synchronusly*, the event will be fired immediately with:
```c++
AIAC_EBUS->DispatchEvent(std::make_shared<SmtHappenedEvent>(param))
```
Or *a-synchronusly*, the event will be stored in the *bus* queue and executed in the main loop, before any layer frame calls:
```c++
IAC_EBUS->EnqueueEvent(std::make_shared<CameraCalibrationLoadedEvent>(filePathName));
```
> Note that you need to pass a `std::shared_ptr<Event>` to the event raisers.

#### How to add events
First Add the event type in `Event.h` if it does not exist already:
```c++
enum class EventType
    {
        None = 0,
        AppClose,
        SLAMMapLoaded, SLAMVocabularyLoaded,
        CameraCalibrationLoaded,
        ExampleCalled  // <-- example
        /* add types of events here */
    };
```
And a category in the same file:
```c++
enum EventCategory
    {
        None = 0,
        EventCategoryApplication =              BIT(0),
        EventCategorySLAM =                     BIT(1),
        EventCategoryCamera =                   BIT(2),
        EventCategoryExample =                  BIT(3)  // <-- example
        /* add event category here */
    };
```
Next, create a new event file with a class that inherits from `class Event`, as an example `ExampleEvent.h`. Remeber to add to the parent constructor *(a)* EventType, *(b)* EventCategory and *(c)* (accessory, by default 0) the prority at which the event needs to be executed, the bigger the number the sooner in the queue it will be fired:
```c++
namespace AIAC
{
    class ExampleCalledEvent : public Event
    {
    public:
        explicit ExampleCalledEvent(const std::string param)
            : Event(EventType::ExampleCalled, EventCategory::EventCategoryExample, 100), m_Param(param)
        {}

        void OnExampleCalled();

    private:
        std::string m_Param;
    };
}
```
Do not forget to add the header to `AIAC.h` in the correct order.
``` c++
#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/ExampleEvent.h"
/* >> add types of events here << */
#include "AIAC/EventSys/EventBus.h"
```
In the declaration you can access layers via `AIAC_APP` as usual:
```c++
namespace AIAC
{
    void ExampleCalledEvent::OnExampleCalled()
    {
        AIAC_APP.GetLayer<LayerName>()->Func(m_Param);
    }
}
```
Finally you just need to add a listener to the `Init()` function of `EventBus.h`:
```c++
#include "AIAC/EventSys/ExampleEvent.h"

m_EventQueue.appendListener(EventType::ExampleCalled, [](const EventPointer& event) {
                auto& slamEvent = static_cast<ExampleCalledEvent&>(*event);
                slamEvent.OnExampleCalled();
            });
```

### Logging
To log use the following MACROS. All the code is contained in `Log.hpp` and `Log.cpp`. 
```c++
AIAC_INFO("test_core_info");
AIAC_WARN("test_core_warn");
AIAC_CRITICAL("test_core_critical");
AIAC_DEBUG("test_core_debug");
AIAC_ERROR("test_core_error");
```
The output is like so:
```bash
[source main.cpp] [function main] [line 32] [16:30:05] APP: test
```
The logging can be silenced by setting OFF the option in the main `CMakeLists.txt` and do clean reconfiguration.
```cmake
option(SILENT_LOGGING "Do not log messages in the terminal of on." ON)
```

### GO System
To add, remove or get Geometric Objects (GO) from any layer:
```c++
#include "AIAC/GOSys/GO.h"

uint32_t idPt1 = GOPoint::Add(1, 1, 1);             // create a point
auto pt1 = GOPoint::Get(idPt1);                     // get the point
float x = pt1->X();                                 // access GO properties
auto pts = GOPoint::GetAll();                       // access all GO of one type
GOPoint::Remove(idPt1);                             // remove the point from registry
```
Note the the Constructor for each GO is private, the only way to instance it is to use the `Add()` static function.

The **G**eometric **O**bject System allows to add objects to the 3D scene before to render them. Having a geometric entity prior to the OpenGL Render allows to calculates relations between geometries to obtain live feedbacks (e.g. drilling depth). Files can be found in `/GOSys`.

The GOSystem is composed of two components:
- `GOPrimitives.h/cpp` (a library which stores `GOPoint`, `GOLine`, `GOText`, etc)
- `GORegistry.h/cpp` (an API which interacts with the map. Note that it has to recive only smart pointers to avoid [object slicing](https://stackoverflow.com/questions/274626/what-is-object-slicing) since we pass heirs of `GOPrimitive`.)



### Renderer API
The renderer API is separated into two parts:
1. `GlUtils.h`: Provides a convenient interface to interact with OpenGL, can draw 3 types of object: `Point`, `Line`, and `Triangle`
2. `RenderAPI.h`: A high level API for drawing `GO` and other shapes, including `Slam Map`, `Circle`, `Cylinder`, `Mesh`, and `Text`.

#### GlUtils.h
##### Point
```c++
void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec4> &colors, GLfloat pointSize);
void glDrawPoints3d(const std::vector<glm::vec3> &vertices, const glm::vec4 &color, GLfloat pointSize);
```
- `vertices`: A vector of 3d points, indicate the position of the vertices.
- `colors`: A RGBA(0~1.0) color, can be either a single `glm::vec4` or a vector with the same size of the `vertices`. 
- `pointSize`: The size of the point.

##### Line
```c++
void glDrawLines3d(const std::vector<glm::vec3> &edges, const std::vector<glm::vec4> &colors);
void glDrawLines3d(const std::vector<glm::vec3> &edges, const glm::vec4 &color);

/* 
 * (0, 1, 0) --- (1, 0, 0)
 *     |             |
 *     |             |
 *     |             |
 * (0, 0, 0) --- (0, 0, 1)
 * 
 * If you want to draw a square like this, you should construct the `edges` as:
 * [
 *    (0, 0, 0), (0, 0, 1),
 *    (0, 0, 1), (1, 0, 0),
 *    (1, 0, 0), (0, 1, 0),
 *    (0, 1, 0), (0, 0, 0)
 * ]
 * 
 * */
```
- `edges`: A vector of the edge's end-points.
- `colors`: A RGBA(0~1.0) color, can be either a single `glm::vec4` or a vector with the same size of the `edges`.

##### Triangle
```c++
void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const std::vector<glm::vec4> &colors);
void glDrawTriangles3d(const std::vector<glm::vec3> &vertices, const std::vector<uint32_t> &indices, const glm::vec4 &colors);
/* 
 * P2(0, 1, 0) --- P3(1, 0, 0)
 *     |            /    |
 *     |          /      |
 *     |        /        |
 *     |      /          |
 *     |    /            |
 * P0(0, 0, 0) --- P1(0, 0, 1)
 * 
 * If you want to draw a mesh of square like this, you should construct the `edges` as:
 * [
 *    (0, 0, 0), // P0
 *    (0, 0, 1), // P1
 *    (1, 0, 0), // P2
 *    (0, 1, 0), // P3
 * ]
 * with `indices`:
 * [
 *     0, 1, 3, // Right-bottom triangle
 *     3, 2, 0  // Left-top triangle
 * ]
 * */
```
- `vertices`: A vector of 3d points, indicate the position of the vertices.
- `indices`: A vector of all triangle's indices.
- `colors`: A RGBA(0~1.0) color, can be either a single `glm::vec4` or a vector with the same size of the vertices.

#### RenderAPI.h
##### GO
An implicit type casting is implemented, simply call the `DrawGo` function in the `Render.cpp`'s function `OnRender()`:
```c++
void DrawGO(const shared_ptr<GOPrimitive>& goPrimitive);
void DrawGOs(const std::vector<shared_ptr<GOPrimitive>>& goPrimitive);
```
Otherwise, if you know the type you want to draw, you can also use the specific function:
```c++
// All function follows this structure:
void DrawType(const GOType& goType);
void DrawTypes(const std::vector<std::shared_ptr<GOType>>& goTypes);

// For example, GOLine can be drawn with
void DrawLine(const GOLine& goLine);
void DrawLines(const std::vector<std::shared_ptr<GOLine>>& goLines);
```

##### Slam Map
```c++
void DrawSlamMap(const shared_ptr<tslam::Map> &map, const glm::vec4 &color, float pointSize);
```
- `map`: The map itself.
- `color`: The color of the point clouds.
- `pointSize`: The point cloud's size.

`other shapes`

##### Line
Draw a line base on two glm::vec3.
```c++
void DrawLine(const glm::vec3 &p1, const glm::vec3 &p2, float weight = GOWeight::Default, const glm::vec4 &color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
```
* `p1` First point.
* `p2` Second point.
* `weight` Weight of the line.
* `color` RGBA Color of the line.

Draw multiple lines.
```c++
void DrawLines(const vector<glm::vec3> &vertices, float weight, const glm::vec4 &color);
```
* `vertices` A vector of glm::vec3. If you have line [p1, p2] and [p2, p3], the vector should be construct as [p1, p2, p2, p3, ...]
* `weight` Weight of the line.
* `color` RGBA Color of the line.
*/

##### Circle
```c++
void DrawCircle(glm::vec3 center, glm::vec3 normal, float radius, glm::vec4 color, glm::vec4 edgeColor, float edgeWeight, int sectorNum = 24);
```
* `center` Center of the circle.
* `normal` The normal of plane on which the circle lays.
* `radius` Radius of the circle.
* `color` RGBA Color of the face.
* `edgeColor` RGBA Color of the edge.
* `edgeWeight` Weight of the edge.
* `sectorNum` Number of sectors, can be derived from `GetSectorNum(radius)`.

##### Cylinder
Draw a Cylinder, this is also used for drawing lines with heavy weight (>1.0f).
```c++
void DrawCylinder(const glm::vec3 &baseCenter, const glm::vec3 &topCenter, GLfloat radius, glm::vec4 color, glm::vec4 edgeColor, int sectorNum = 24);
```
* `baseCenter` Base center (bottom) of the cylinder.
* `topCenter` Top center (top) of the cylinder.
* `radius` Radius of the cylinder; For drawing line, radius = weight * WEIGHT_TO_CYLINDER_RADIUS_RATE.
* `color` Color of the cylinder.
* `edgeColor` The color of the edges of the caps.
* `sectorNum` Number of sectors of the cylinder. Can call `GetSectorNum(radius)` to get the default value.