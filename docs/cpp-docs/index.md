# C++ docs

Welcome to the C++ documentation for AC. This documentation is auto-generated using [mkDoxy](https://github.com/JakubAndrysek/MkDoxy/tree/main) for generating documentation from annotated C++ source code.

The main entry point of the project is the [AIAC.h](src/AIAC.h) file. Here you can find all the major headers for the project.

``` cpp title="src/AIAC.h"
#pragma once

#include "AIAC/GlHeader.h"

#include "AIAC/Config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "AIAC/Base.h"
#include "AIAC/Log.h"
#include "AIAC/Assert.h"

#include "AIAC/TouchMonitor.h"
#include "AIAC/Window.h"

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"

#include "AIAC/Image.h"
#include "AIAC/Camera.h"
#include "AIAC/DLoader.h"

#include "AIAC/Layer.h"
#include "AIAC/LayerCamera.h"
#include "AIAC/LayerCameraCalib.h"
#include "AIAC/LayerSlam.h"
#include "AIAC/LayerUI.h"
#include "AIAC/LayerModel.h"
#include "AIAC/LayerToolhead.h"
#include "AIAC/LayerFeedback.h"
#include "AIAC/LayerUtils.h"
#include "AIAC/LayerLogRecorder.h"

#include "AIAC/Render/Renderer.h"
#include "AIAC/GOSys/GO.h"

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/ApplicationEvent.h"

/* >> add types of events here << */
#include "AIAC/EventSys/EventBus.h"

#include "AIAC/Application.h"
```

The documentation is organized into several sections to help you navigate through the different components of the project. Each section provides detailed information about classes, functions, variables, and other elements of the codebase. Below is a high-level overview of the structure of the *code base documentation*:

| Section            | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| **[Files](../acdoxygen/files.md)**          | Contains detailed information about the files in the project, including file-level documentation and references to classes and functions defined within each file. |
| **[Functions](../acdoxygen/functions.md)**      | A list of all global functions in the project, detailing their signatures, parameters, and return types. |
| **[Class List](../acdoxygen/annotated.md)**     | A comprehensive list of all classes in the project, providing quick access to class documentation. |
| **[Class Hierarchy](../acdoxygen/hierarchy.md)**| A hierarchical view of the class inheritance structure, showing the relationships between base and derived classes. |
| **[Class Members](../acdoxygen/class_members.md)**  | Detailed information about the members of each class, including functions, variables, typedefs, and enumerations. |
| **[Typedefs](../acdoxygen/hierarchy.md)**       | A list of all typedefs in the project, providing type aliases used throughout the codebase. |
| **[Namespace List](../acdoxygen/namespaces.md)** | A list of all namespaces in the project, providing an overview of the namespace structure. |
| **[Namespace Members](../acdoxygen/namespace_members.md)** | Detailed information about the members of each namespace, including functions, variables, typedefs, and enumerations. |
| **[Variables](../acdoxygen/variables.md)**      | A list of all global variables in the project, including their types and descriptions. |
| **[Macros](../acdoxygen/macros.md)**         | A list of all macros in the project, providing preprocessor definitions used throughout the codebase. |