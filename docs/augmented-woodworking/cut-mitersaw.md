---
tags:
  - acim
  - UI
  - cut
  - circular-blade
  - fab
---

Here's the step-by-step guide on how to use augmented-carpentry with any miter saw to realize basic joints (cross-lap, half-lap, and butt joints). The guidance system is similar to the one for [circular saws](augmented-circular-saw.md).

<div class="video-wrapper"><iframe src="https://player.vimeo.com/video/1069137536?h=eb40e565bc&amp;badge=0&amp;autopause=0&amp;title=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture; clipboard-write; encrypted-media" style="position:absolute;top:0;left:0;width:100%;height:100%;"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

<br>

# Step-by-step


<!-- Intro to UI and feedback components (pos, rot, depth) -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/cut_mitersaw_ui.png)
</figure>
<div class="description" markdown>
This is the overview of the feedback and widget system to assist you during the cut.

**a** - Feedback for balde position (in cm). The goal is to diminish the line length corresponding to the position error, to zero (green).

**b** - Feedback for blade rotation (in degrees). The goal is to diminish the line length corresponding to the angle error, to zero (green).

**c** - Feedback for balde depth (in mm). The goal is to to get to a value close to zero (green). In `00|00`, the first tow digit represent the distance of the projected blade to the bottom face of the cut, and the last two digits represent the closest distance from the blade to the bottom face of the cut (two purple-magenta points).

**d** - Projection of the blade thickness on the face to be cut.
</div>
</div>


<!-- Rotation: rotate blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069143962?h=2fbeababdf&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
        class="frame-overlay"
    />
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/overlay_symbol_rotate.png"
        class="symbol-overlay"
    />
</div>
</figure>
<div class="description" markdown>
Adjust the rotation (**b**) until the indicator becomes green.
</div>
</div>


<!-- Position: placing blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069145307?h=e4cbec299a&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
Adjust now the position (**a**) until the indicator becomes green.
</div>
</div>


<!-- Depth: adjust blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069151977?h=b8edaab81f&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
With miter saws the adjustement of the depth can be done on the go. Lower the blade and stop to the right height (**d** `00|00` first value is 0).
</div>
</div>


<!-- Guide the cut towards the end -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069155866?h=a93c4887d4&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0"
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
        class="frame-overlay"
    />
</div>
</figure>
<div class="description" markdown>
Push through the end of the cut. With the miter saw it is easier than the [circular saw](augmented-circular-saw.md) since you have a mechanical fixed guide.
</div>
</div>


<!-- Do the second cut and fill the cuts in the middle -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069157914?h=3efa55f426&amp;player_id=0&amp;app_id=58479&amp;byline=0&amp;portrait=0" 
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="https://github.com/ibois-epfl/augmented-carpentry/blob/main/docs/assets/images/frame-overlay.png?raw=true"
        class="frame-overlay"
    />
</div>
</figure>
<div class="description" markdown>
As for the [circular saw](augmented-circular-saw.md), do the second cut and slots of the joints.
</div>
</div>


<!-- Guide the cut towards the end -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1069165455?h=a7509580fd&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0"
        frameborder="0" 
        allow="autoplay; fullscreen; picture-in-picture" 
        allowfullscreen>
    </iframe>
    <img 
        src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
        class="frame-overlay"
    />
</div>
</figure>
<div class="description" markdown>
You can inspect the cuts if the overlay matches the cut. If not, you can adjust the cut by repeating the steps above.
</div>
</div>


<!-- Set as done the current joint -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/cut_mitersaw_done.png)
</figure>
<div class="description" markdown>
Once you are done hit the button **Done** to set the joint as done (*).
</div>
</div>




<!-- hint butt joint: ui + cut + inspection -->
!!! cut-joint "End half-lap joints"
    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    ![Image title](../assets/images/woodworking/cut_mitersaw_bjoint_ui.png)
    </figure>
    <div class="admonition-seveinch-desc" markdown>
    For butt joints with the miter saw the feedback interface is greatly simplified. Basically there is only one visual cue to follow, resuming position and rotation. The depth is not relevant for this type of joint.

    **a** - execution model bounding box

    **b** - selected butt joint face

    **c** - position and rotation feedback

    **d** - projection of the blade thickness on the timber volume

    **e** - scanned model bounding box
    </div>
    </div>

    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    <div class="video-container">
        <iframe 
            src="https://player.vimeo.com/video/1069211983?h=a07421a9df&amp;player_id=0&amp;app_id=58479&amp;byline=0&amp;portrait=0" 
            frameborder="0" 
            allow="autoplay; fullscreen; picture-in-picture" 
            allowfullscreen>
        </iframe>
        <img 
            src="https://github.com/ibois-epfl/augmented-carpentry/blob/main/docs/assets/images/frame-overlay.png?raw=true"
            class="frame-overlay"
        />
    </div>
    </figure>
    <div class="admonition-seveinch-desc" markdown>
    Follow the only visual cue to adjust the position and rotation of the blade. Once the indicator is green, you can proceed to the cut.
    </div>
    </div>

    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    <div class="video-container">
        <iframe 
            src="https://player.vimeo.com/video/1069207656?h=852800cba6&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0"
            frameborder="0" 
            allow="autoplay; fullscreen; picture-in-picture" 
            allowfullscreen>
        </iframe>
        <img 
            src="{{ config.site_url }}/assets/images/woodworking/frame-overlay.png"
            class="frame-overlay"
        />
    </div>
    </figure>
    <div class="admonition-seveinch-desc" markdown>
    Inspect the butt joint. If the overlay does not match the cut, you can adjust the cut by repeating the steps above.
    </div>
    </div>