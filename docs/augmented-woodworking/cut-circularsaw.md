---
tags:
  - acim
  - UI
  - cut
  - circular-blade
  - fab
---

Description


<br>

# Step-by-step

<!-- TODO: Select the current cut -->

<!-- TODO: Intro to UI and feedback components (pos, rot, depth) -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/cut_circular_uigen.png)
</figure>
<div class="description" markdown>
This is the overview of the feedback and widget system to assist you during the cut.

**a** - Feedback for balde position (in cm). The goal is to diminish the line length corresponding to the position error, to zero (green).

**b** - Feedback for blade rotation (in degrees). The goal is to diminish the line length corresponding to the angle error, to zero (green).

**c** - Feedback for balde depth (in mm). The goal is to to get to a value close to zero (green). In `00|35`, the first tow digit represent the distance of the projected blade to the bottom face of the cut, and the last two digits represent the closest distance from the blade to the bottom face of the cut (two purple-magenta points).

**d** - Unselected face.

**e** - The current label name of the cut.

**f** - Auto-selected face to be cut. Face is auto-selected based on the blade position and orientation.

**g** - Projection of the blade thickness on the face to be cut.
</div>
</div>

<!-- Depth: adjust blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1067794618?h=ce5466e413&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
        class="frame-overlay"
    />
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/overlay_symbol_updow.png"
        class="symbol-overlay"
    />
</div>
</figure>
<div class="description" markdown>
Adjust first the height of the blade (**c**).
</div>
</div>

<!-- Position: placing blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1067814264?h=98b3b28664&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
        class="frame-overlay"
    />
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/overlay_symbol_leftright.png"
        class="symbol-overlay"
    />
</div>
</figure>
<div class="description" markdown>
Adjust now the position (**a**).
</div>
</div>


<!-- TODO: Rotation: rotate blade -->

<!-- TODO: Guide the cut towards the end -->

<!-- TODO: Quick inspection to see the overlap -->

<!-- TODO: Set as done the current cut -->