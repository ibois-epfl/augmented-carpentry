---
tags:
  - map
  - UI
  - fab
---

<!-- FIXME: Get rid of the title in the page? -->

Before you map the piece, stick the tags

<!-- TODO: Add tags to the timber piece -->

Go around the piece to map it

<!-- TODO: Add the video side by side of the mapping of one piece (maybe with drone??) -->


<!-- Start the mapping -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/map_selectstart_01.png)
</figure>
<div class="description" markdown>
Click the button **Start Mapping** (*) to start the mapping process.
</div>
</div>

<!-- Mapping interface -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/map_inside_map_02.png)
</figure>
<div class="description" markdown>
The mapping is now started.

**a** - landmark feature points used to facilitate camera localization

**b** - tags already acquired (yellow)

**c** - newly detected tags pending acquisition (blue)

**d** - map-building overview

**e** - optimization parameters

**f** - reconstruction parameters for generating a mesh box from the registered tags

**g** - commands to save or discard the current mapping recording
</div>
</div>

<!-- Mid mapping NB: autovideo-->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1065559795?h=afb4e097b9&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
Go around the timber piece, turn it when needed, and capture as many tags as possible.
</div>
</div>

<!-- Mapping closing -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
![Image title](../assets/images/woodworking/map_confirm_map_03.png)
</figure>
<div class="description" markdown>
Click on the **Save & Exit** button to save the mapping and start the processing.
</div>
</div>

<!-- TODO: Load acim model (UI interface to select acim navigation) -->

<!-- TODO: Visualize the piece with 3D model overlay -->

<!-- FIXME: add the tab block inside, see how it can work>
<!-- In case of reconstruction failure -->
<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1065422379?h=3461c28610&amp;badge=1&amp;autopause=0&amp;player_id=0&amp;app_id=58479&amp;title=1&amp;byline=0&amp;portrait=0" 
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
In case the reconstruction fails, follow **this** procedure. You can try to reconstruct the piece with different parameters. We have several presets available to try based on the element's length.
</div>
</div>