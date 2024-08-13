# augmented-carpentry
The PyPi package for the augmented-carpentry project.

## Replayer
The replayer is used to generate video from the log. These components works together for visualizing and export the scene.
1. Initializer: The initializer loads everything according to the given path and experiment id, including the log which stores the transformation of all 3D models, ACIM, and TTool Mesh.
2. Scene generator: Takes a frame id as input, show the scene of the given frame. This is used to inspecting the transformation and identify the start/end of the sequence.
3. Scene sequence generator: Takes frame start/end id as input, exporting the scene frame by frame.
4. Video capturer: Triggered by `scene sequence generator` with `frame index`. Export the frame as .png and use ffmpeg to compose the video. If `clean_imgs` is set to True, the exported .png files will be deleted after the video is generated.
5. Image cleaner: For manually cleaning the .png files.

### Usage
1. Setting up all the required paths.
2. Using the `Scene generator` with a slider to determine the start / end frame and adjust the viewport.
3. Disable the geometry preview of `Scene generator`, enable the preview for `Scene sequence generator`.
4. Click `reset` button and flip the toggle of `run` to `True`, the program will start to export frames. When all the frame is exported, a video will be generated afterward.

### Old logs
Some old logs have error for the ACIM transformation. Here's the status of these old logs. 'O' means the log has no problem, and 'X' means the log has problem:
```
A001: O
A003: X
AC01: O
AC02: O (only half?)
AC03: X
AC04: X
B003: X
B004: O
BD01: X
BD02: X
BD03: X (only 168 frames?)
BD04: ? (Transformation seems correct, but log is almost empty)
C001: X
C002: X (no TTool pose)
C003: O
C004: O
D001: O
D002: X (no TTool pose)
D003: X
D004: X
W001_3: X
X001: X
X002: X
Y001: O
Z001: O
Z002: O
```