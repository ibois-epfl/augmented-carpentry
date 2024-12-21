---
tags:
  - AREngine
  - render
---


# AR rendering

## Main Rendering Pipeline
The rendering system manages two viewports during the fabrication phase: the main AR view and the 3D viewport. The AR view combines captured images with virtual objects, such as CAD models and feedback graphics, to provide clear and intuitive instructions. The 3D viewport serves as an interface for navigating the entire scene, enabling users to easily inspect different components. The system consists of the following key components:

1. [`Renderer.h`](https://github.com/ibois-epfl/augmented-carpentry/blob/main/src/AIAC/Render/Renderer.h): Defines the core logic of the rendering pipeline and manages essential attributes.
2. [`Viewport.h`](https://github.com/ibois-epfl/augmented-carpentry/blob/main/src/AIAC/Render/Viewport.h): Handles the sub-frame buffer. The renderer calls [`Activate()`](https://github.com/ibois-epfl/augmented-carpentry/blob/e29ed367a88a3ec412fd1dc5ba136c6cc93f37aa/src/AIAC/Render/Viewport.cpp#L42) to switch the buffer for rendering.
3. [`GLObject.h`](https://github.com/ibois-epfl/augmented-carpentry/blob/main/src/AIAC/Render/GLObject.h): Helps GO manage OpenGL resources, allocating memory and buffering data for rendering. Each GO may contain one or multiple GLObjects stored in a list. By invoking Draw(), the content is rendered to the currently active frame buffer.

The [`Renderer::OnRender()`](https://github.com/ibois-epfl/augmented-carpentry/blob/e29ed367a88a3ec412fd1dc5ba136c6cc93f37aa/src/AIAC/Render/Renderer.cpp#L115) function is executed after all layers are processed. Within this function:

1. [`RenderMainView()`](https://github.com/ibois-epfl/augmented-carpentry/blob/e29ed367a88a3ec412fd1dc5ba136c6cc93f37aa/src/AIAC/Render/Renderer.cpp#L253) renders the main AR view by calculating the projection matrix using the estimated position from `LayerSLAM` and overlays all geometry from the `GORegistry` onto the captured image.
2. [`RenderGlobalView()`](https://github.com/ibois-epfl/augmented-carpentry/blob/e29ed367a88a3ec412fd1dc5ba136c6cc93f37aa/src/AIAC/Render/Renderer.cpp#L205) switches the frame buffer to the 3D viewport and renders the geometry with a projection based on the user's navigation.

Text rendering is handled separately via [`TextRenderer`](https://github.com/ibois-epfl/augmented-carpentry/blob/main/src/AIAC/Render/TextRenderer.h), where a special projection method and a different shader are used, so that the text always faces the screen, rather than floating in 3D space.

## Sub-process rendering

While performing camera calibration or in the mapping phase, the main view is blocked and will not be rendered. Instead, a sub-view will be rendered. In the function [`Renderer::OnRender()`](https://github.com/ibois-epfl/augmented-carpentry/blob/e29ed367a88a3ec412fd1dc5ba136c6cc93f37aa/src/AIAC/Render/Renderer.cpp#L115), it checkes if the system is currently in a special condition, and calls the corresponding functions, ` RenderCamCalibView()` or `RenderMappingView()`.
