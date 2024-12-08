---
title: 'Augmented Reality UNIX C++ Engine for Enhanced Visual Guidance in Digital Fabrication'
tags:
  - C++
  - UNIX
  - augmented reality
  - engine
  - digital fabrication
authors:
  - name: Andrea Settimi
    orcid: 0000-0001-5020-7331
    corresponding: true
    affiliation: 1
  - name: Hong-Bin Yang
    orcid: 0000-0001-8422-5263
    affiliation: 1
  - name: Julien Gamerro
    orcid: 0000-0001-7802-5345
    affiliation: 2
  - name: Yves Weinand
    orcid: 0000-0002-8088-6504
    affiliation: 1

affiliations:
 - name: IBOIS EPFL, Switzerland
   index: 1
 - name: Independent Researcher, Switzerland
   index: 2
date: 18 November 2024
bibliography: paper.bib

---

<!--
# Structure of the paper

- (0) Summary (MAX 50 words) - ANDREA
- (1) Statement of need (MAX 125 words) - ANDREA
- (2.1) Layer-stack flow (MAX 150 words) - ANDREA
- (2.2) Geometry framework (MAX 200 words) - HONG-BIN
- (2.3) AR rendering (MAX 150 words) - HONG-BIN
- (2.4) Computed Feedback System (MAX 150 words) - ANDREA
- (3) Acknowledgements - ANDREA
- (4) References - ANDREA
-->

# Summary  <!-- 55/50 words -->

Augmented Carpentry is a lightweight and fast-developing UNIX C++ engine for prototyping AR applications leveraging bleeding-edge robotic vision research for digital fabrication. It features a modular layer-stack flow, a geometry framework for managing 3D objects, a computed feedback system for visual guidance, and an AR rendering system for synthesizing digital instructions into a simple monocular camera feed.


# Statement of need  <!-- 197/125 words -->

Augmented Carpentry (AC) addresses critical limitations in existing augmented reality (AR) tools for digital fabrication. CompasXR [@compas-xr], the only open-source AR tool available in the digital fabrication field, provides a valuable common platform, particularly for assembly tasks. However, it currently lacks a streamlined integration pipeline for advanced robotic vision technologies due to its reliance on Unity [@unity] and the Windows operating system (OS). In the field of AR fabrication, developers from the current Incon.ai [@incon] represent the peak of AR engine innovation with robotic vision algorithm integration for digital fabrication in research [@sandy:2016; @sandy:2018; @mitterberger:2020], nevertheless, its codebase remains unavailable to the public.

AC aims to fill this gap by providing a lightweight, open-source, and UNIX-compatible C++ engine for AR applications in digital fabrication. Its software architecture is similar to existing free engines [@godot; @torque3d; @ezengine], yet it prioritizes rapid prototyping, flexibility, and customization for extended reality (XR) manufacturing using accessible sensors and hardware. Unlike feature-rich game engines with excessive functionalities or proprietary constraints [@unity; @unreal], AC is lightweight, aided by the adoption of a bloat-free UI system [@dearimgui], and maintains full compatibility with Linux systems—crucial for integrating the latest open-source robotic vision technologies in AR manufacturing.

## Layer-stack flow  <!-- 198/150 words -->

The main AR engine is managed by a layer-stack flow. Designed as a modular system, each layer encapsulates the code for a specific domain of the AR application, such as camera processing, sensor's self-localization, object tracking, UI, and rendering. The general order and expansion of these layers can be configured in the top-level main file `ACApp.cpp`. This architecture provides flexibility to customize key AR features as needed, including integrating new sensors, modifying the rendering pipeline, or adapting camera pose estimation methods. For instance, users can implement pose estimation based on tags [@salinas:2019], features [@compos:2021], or hybrid [@settimi:2024] approaches as supported by the software out of the box.

Each layer in the stack inherits from a superclass interface defined in `Layer.h`, which includes event-like methods triggered at various points during frame processing (e.g., `OnFrameAwake()`, `OnFrameStart()`, etc). These methods are invoked by the main `Run()` function in the singleton application loop from `Application.h`. This design allows application tasks to be containerized and executed sequentially while facilitating data exchange between specific layers through the `AIAC_APP` macro, enabling the retrieval of any particular layer data. Exchange between layers can also take place in a more structured way with the integrated event system (`ApplicationEvent.h`), which is capable of queuing events from layers and trigger them in the next main loop.

![Illustration of the layer-stack design and the main loop for the AR engine.](fig_layer-stack.svg){ width=60%}


## Geometry framework  <!-- 157/200 words -->

The geometry framework provides a uniform infrastructure to handle all 3D objects present in the scene, including the CAD model, scanned models, and the fabrication instructions. This framework not only allows application layers to interact with the 3D object easily but is also tightly integrated with the rendering system and manages the OpenGL resources implicitly to ease the work for application layers.

The geometry is classified by the following primitive shapes: point, line, circle, cylinder, polyline, triangle, mesh, and text. Each primitive shape is a class (e.g. `GOPoint`, `GOLine`, `GOCircle`, etc) inheriting from the base class `GOPrimitive`, where GO stands for Geometry Object. The system also maintains a global table `GORegistry` to keep track of all the geometry objects. When a GO initializes, it registers itself in a global table with a unique UUID. As the table is exposed to the entire system, application layers can acquire specific objects through their UUIDs or iterate through all objects to perform operations.


## Computed Feedback System  <!-- 170/150 words -->

The `LayerFeedback.h` module manages the computation of all essential data required to provide visual guidance to users during the fabrication process. Feedback computation primarily relies on data retrieved from two preceding layers:

1. `LayerModel.h`: contains the execution model and geometries associated with the currently active hole or cut.
2. `LayerToolhead.h`: provides similar information, but specific to the toolhead currently attached to the tool.

Feedback is categorized based on similar operations, such as drilling (`HoleFeedback.h`), circular cutting (`CutCircularSawFeedback.h`), and chainsaw cutting (`CutChainSawFeedback.h`). Each feedback category inherits from an interface class (`AIAC/Feedback/FabFeedback.h`), which defines high-level control functions like `Update()`, `Activate()`, and `Deactivate()`.

The visual guidance for each tool may consist of multiple visual cues, most of which are implemented using the template `FeedbackVisualizer.h`. These internal components (e.g., `CutBladeThicknessVisualizer.h` or `CutPlaneVisualizer.h`) handle their own geometric visual cue calculations and store representations as `GO` instances in a member vector of the corresponding superclass. Visualization of these `GO` elements, and thus the feedback itself, can be selectively enabled or entirely toggled on/off using the `Activate()` and `Deactivate()` functions.


![Dataflow for the functioning of the Augmented Carpentry's feedback system.](fig_feedback-sys.svg){ width=100%}


## AR rendering  <!-- 202/150 words>
The rendering system synthesizes the captured video and virtual objects, such as CAD models and feedback graphics, to create an AR view.

The rendering system is built using OpenGL, where the infrastructure is mainly defined in `Renderer.h`. When a GOPrimitive object is constructed or modified, a corresponding OpenGL instance is initialized. As OpenGL only renders points, lines, and meshes, the primitive shapes of circles and cylinders construct corresponding meshes implicitly. Additionally, the geometry system allows users to define the width of lines, while OpenGL's line rendering does not. Therefore, a mesh of a cylinder is created for rendering thick lines.

Text rendering is handled separately using `TextRenderer.h` since we intend to make the text always face the screen instead of floating in 3D space. To achieve this, a different shader is created to perform a unique projection method.

On each frame, the rendering layer (`LayerRendering.h`) takes the estimated camera position from the SLAM layer to calculate the projection matrix and iterates through the geometry table to render visible objects. While iterating, the system checks the type of shape and calls the corresponding function to render either text or non-text objects, additively depicting objects on the captured image, ultimately creating the AR view.


# Acknowledgements  <!-- 45 words -->

We would like to thank all the contributors to the Augmented Carpentry project, including the developers, researchers, and users who have provided valuable feedback and suggestions. Special thanks to the GIS and the Center for Imaging EPFL groups, for their support throughout the development process.

# References