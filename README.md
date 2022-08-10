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

### Naming convention
Here's the naming convention for this project:
- `localVariable`: lowerCamelCase.
- `m_PrivateVariable`: Hungarian notation with UpperCamelCase.
- `APP_SPEC`: Constants with SNAKE_UPPER_CASE.
- All the other things uses UpperCamelCase.

Here's an example:
```c++
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
```

### Config
We use an [.ini]() file to store the config parameters of the application. The parser is derived from [this project]() but with some modification. Here's an example:
- Declaration:
```cpp
// Just include this header
#include "AIAC/Config.h"

// Open file "config.ini".
// The second param indicate if the file need to be update when 
// InsertEntry() and UpdateEntry() is called.
// The initialization happens in the very beginning of `ACApp.cpp`.
inih::Ini config("config.ini", true);
```

- Usage
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

        /// Is called once per loop and takes care of everything related ot UI
        virtual void OnUIRender() {}

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

### Getting other layers' variables
To get other layers' variables use a small query function from the Application class. In the case of accessing test_a of layerA from e.g. layerB:
```c++
AIAC::Application& app = AIAC::Application::GetInstance();
app.GetLayer<AIAC::LayerA>()->test_a
```

### Logging
To log use the following MACROS. All the code is contained in `Log.hpp` and `Log.cpp`. 
```c++
AIAC_CORE_INFO("test_core_info");
AIAC_CORE_WARN("test_core_warn");
AIAC_CORE_CRITICAL("test_core_critical");
AIAC_CORE_DEBUG("test_core_debug");
AIAC_CORE_ERROR("test_core_error");
```
The output is like so:
```bash
[source main.cpp] [function main] [line 32] [16:30:05] CORE: test
```
The logging can be silenced by setting OFF the option in the main `CMakeLists.txt` and do clean reconfiguration.
```cmake
option(SILENT_LOGGING "Do not log messages in the terminal of on." ON)
```