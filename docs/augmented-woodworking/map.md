---
tags:
  - map
  - UI
  - fab
---

Print the [tags](../hardware/stickers.md) and stick them to the timber piece. Cover the middle of each face of the timber beam with the tags. Once it is done, mapping can start. The mapping is the process of capturing the tags with the camera to create a 3D model of the timber piece. By doing this, the system will be able to track the timber piece in real-time during the fabrication.

<!-- FIXME: do the round border -->
<div class="video-wrapper"><iframe src="https://player.vimeo.com/video/1065880051?h=ea7b8858ac&amp;badge=0&amp;autopause=0&amp;title=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture; clipboard-write; encrypted-media" style="position:absolute;top:0;left:0;width:100%;height:100%;"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

<br>

# Step-by-step

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
Go around the timber piece, turn it when needed, and capture as many tags as possible. Start from the middle of the beam and go on the extremities, this will help redistribute the error of the tags detection uniformly.
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

<div class="sevinch-display-tutorial" markdown>
<figure markdown>
<div class="video-container">
    <iframe 
        src="https://player.vimeo.com/video/1065789261?h=8a4c544793&amp;background=1&amp;autopause=0&amp;loop=1&amp;autoplay=1&amp;muted=1&amp;controls=0&amp;title=0&amp;byline=0&amp;portrait=0" 
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
Once the map is loaded together with the `.acim` model, you can visualize if the piece is correctly reconstructed (black lines) and if the model is correctly aligned with the piece.
</div>
</div>

<br>

!!! example "Troubleshooting a failed reconstruction"
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
    <div markdown>
    In case the reconstruction fails, follow **this** procedure. You can try to reconstruct the piece with different parameters. We have several presets available to try based on the element's dimensions.
    </div>
    </div>
    <br>

!!! bug "Limit to 3 meters elements for stable mapping"
    <div class="sevinch-display-tutorial" markdown>
    <figure markdown>
    <div class="video-container">
        <iframe 
            src="https://player.vimeo.com/video/1065817712?h=1b87096797&amp;badge=1&amp;autopause=0&amp;player_id=0&amp;app_id=58479&amp;title=1&amp;byline=0&amp;portrait=0" 
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
    <div markdown>
    For now if the beam exceeds `3 m`, the system will sometimes fail to map the piece. In this case, you can try to reduce the number of tags in e.g., the middle of the beam.
    </div>
    </div>