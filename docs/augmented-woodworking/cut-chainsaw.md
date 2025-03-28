---
tags:
  - acim
  - UI
  - cut
  - chainsaw-blade
  - fab
---

Here's the step-by-step guide on how to use augmented-carpentry with any circular saw to realize basic woodworking operations.

<div class="video-wrapper"><iframe src="https://player.vimeo.com/video/1068850648?h=c7dce822c4&amp;badge=0&amp;autopause=0&amp;title=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture; clipboard-write; encrypted-media" style="position:absolute;top:0;left:0;width:100%;height:100%;"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>


<br>

# Step-by-step


<!-- Intro to UI and feedback components (pos, rot, depth) -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/cut_chainsaw_ui.png)
</figure>
<div class="description" markdown>
The assistance interface for the chainsaw is composed by the following elements:

**a** - Feedback for balde position (in cm). The goal is to diminish the line length corresponding to the position error, to zero (green).

**b** - Feedback for blade rotation (in degrees). The goal is to diminish the line length corresponding to the angle error, to zero (green).

**c** - This is particular to the chainsaw feedback system. In order to obtain straight cuts both the base and tip of the chain needs to have equal heights. The yellow lines represent the distance to the bottom faces of bottom and tip blade. The idea is to have equidistant heights so that the two lines become green. The value `d:00` represents the shortest distances of both.

**d** - The blade projection on the bottom face.
</div>
</div>


<!-- Position: placing blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1068875476?h=f7f93dcf44&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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


<!-- Rotation: rotate blade -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1068880690?h=95fec4aad5&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
Adjust now the rotation (**b**) until the indicator becomes green.
</div>
</div>


<!-- Depth: adjust blade while cutting-->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1068890700?h=aae78228dc&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
You can now start the cut. Adjust the two ends (**c**) so that the blade is straight. Watch out the `d:00` when it gets to zero, the cut is done.
</div>
</div>


<!-- Do the second cut and fill the cuts in the middle, and set as done -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1068897985?h=3b964c7200&amp;player_id=0&amp;app_id=58479&amp;byline=0&amp;portrait=0" 
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
Now you can do the other side of the cut and the multiple cuts in between the two ends without augmented feedback.
</div>
</div>


<!-- Clean and inspect the full cut -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1068899592?h=3e8f0602ee&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
Once done, you can inspect the full cut with the augmented overlay.
</div>
</div>


<!-- Set as done the current joint -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/cut_chainsaw_done.png)
</figure>
<div class="description" markdown>
Once you are done hit the button **Done** to set the joint as done (*).
</div>
</div>


<!-- hint: example of single end cut -->
!!! cut-joint "Butt joint"
    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    ![Image title](../assets/images/woodworking/cut_chainsaw_buttjoint_ui.png)
    </figure>
    <div class="admonition-seveinch-desc" markdown>
    For end half-lap joints, the feedback elements are the same as for cross-lap joints. The difference is that the blade will be guided to the end of the cut, and the cut will be done only on one side of the timber.

    **a** - bounding box boundaries

    **b** - chainsaw blade's axis

    **c** - chainsaw blade's thickness

    **d** - joint 3D visualization. This can be particularly useful for having a better understanding of the joint's geometry and the blade's position during the cut.

    **e** - move the 3D view

    **f** - zoom the 3D view

    **g** - selected fix orthographic view
    </div>
    </div>

    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    <div class="video-container">
        <iframe 
            src="https://player.vimeo.com/video/1068903814?h=b4005903e1&amp;player_id=0&amp;app_id=58479&amp;byline=0&amp;portrait=0" 
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
    The system guides you to the end of the single one-face cut. Make sure to keep the position and rotation values green all along.
    </div>
    </div>

!!! danger "Double inclined cuts"
    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    <div class="video-container">
        <iframe 
            src="https://player.vimeo.com/video/1068924530?h=01b80be6ce&amp;player_id=0&amp;app_id=58479&amp;byline=0&amp;portrait=0" 
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
    For double inclined cuts, the rotation feedback will not guide all degrees of freedom. The two degrees of freedom for the rotation will be merged into the same feedback. React intuitivly to the feedback and adjust the rotation until the indicator becomes green.
    </div>
    </div>
    <br>