# Add new tools or mounts

You may end up in a situation where your wood working tool has no mount (:material-circular-saw:) already available or its toolhead (:material-screw-machine-flat-top:) is not digitized and present in the [AC datasets]. In this case you can contribute to the existing datasets of both by following first these instructions.

  [AC datasets]: ../hardwaare/woodworking-tools.md


## 3D Model your items

Chances are that you will be needing to acquire the 3D model of our mount (:material-circular-saw:) or toolhead (:material-screw-machine-flat-top:).

=== ":material-circular-saw:&nbsp;&nbsp; tool mount"

    ![AC mount><>](../assets/images/getting_started/hardware_mounts/animation_mount_1.gif){width="400" class="rounded-corners"}

    For the mount, you can do this by using a 3D scanner or by modeling it yourself. If you are modeling it yourself, you can use [Blender](https://www.blender.org/) or [FreeCAD](https://www.freecadweb.org/) to create the model. Then you can export the model as a `.stl` file with the following naming convention: `toolhead_mount_name.stl`.

    Each STL file follows the naming convention:

    `<type>_<brand>_<model-name>_part.stl`

    - &nbsp;&nbsp;`type`: Indicates the type of mount or the tool category (e.g., "mount", "sensor-holder").

    - &nbsp;&nbsp;`brand`: The woodworking tool brand (e.g., "Makita", "Bosch", "Dewalt").

    - &nbsp;&nbsp;`model-name`: The specific model identification of the tool (e.g., "M3700", "1617EVS").

    - &nbsp;&nbsp;`part`: Optional additional descriptor if multiple parts are required for a single mount assembly (e.g., "base", "clip", "insert").
    
    
    For example, a mount designed for a Makita M3700 router might be named:

    `mount_makita_m3700_base.stl`

    `mount_makita_m3700_clip.stl`

=== ":material-screw-machine-flat-top:&nbsp;&nbsp; toolhead"

    ![AC toolhead><>](../assets/images/getting_started/drill_anim.gif){width="400" class="rounded-corners"}

    ### Photogrammetry

    Obtain a 3D model from a physical tool can be complicated. The idea of photogrammetry is to secure images of the tool from different angels and reconstruct the 3D model from that. Hence, 2 crucial steps need to be done.
    1. Acquiring the photos - at IBOIS, we use 2 different methods depending on the size of the physical objects.
      1.1 When the size is small enough we use the [foldio](https://orangemonkie.com/de/)
      1.2 When the size is too large to fit in the studio, we use the custom made stone scanner.
    2. 3D reconstruction - we use the metashape program and the way we do it can be followed by this [link](https://github.com/ibois-epfl/aiac_synth_data/blob/master/docs/add_drill_bit.md)

    ![2D Image scan](media/Adding-New-Drill-Bit---Toolhead/[1]metashape-reconstruction.png)
    By this approach, you should have. Please not that we name the final 3D object as "model" as a convention
    
    1. `model.obj` - 3D model of the physical tool head.
    2. `model.mtl`<small>optional</small> - complimentary file for the model.obj
    3. `model_occlusion.jpg`<small>optional</small> - occlusion texture of the object from the 3D model reconstruction
    4. `model_normal.jpg`<small>optional</small> - occlusion texture of the object from the 3D model reconstruction
    5. `model.jpg`<small>optional</small> - diffuse map texture of the object from the 3D model reconstruction

    ### Re-scale

    Once the 3D model is obtained, we must re-scale it to the correct size. This can be done in the blender.

    1. Use the measure tool to measure the reference part of the object and physical object. Here the diameter of the circle is measured, which is 1.5681m. 
    ![measure tool](media/Adding-New-Drill-Bit---Toolhead/[2]rescale-measure-large.png)]
    2. Scale the 3D model to to same size as the physical tool head. The physical object is measured to be 0.020m. Hence, the scale factor is 0.020/1.5681 = 0.0127. To do this, press `s` and type in the scale factor. Then, press `enter`.
    ![rescaling the model using the scaling tool](media/Adding-New-Drill-Bit---Toolhead/[2]rescale-scale.png)
    3. Check the scale by measuring the reference part of the object and physical object again. Here the diameter of the circle is measured, which is 0.020m.
    ![final scaled model which has 0.020m of diameter](media/Adding-New-Drill-Bit---Toolhead/[2]rescale-final.png)
    By this step, you should have.
    1. `model.obj` - 3D model that is re-scaled to the precise size of the physical tool head.
    2. `model.mtl`<small>optional</small> - complimentary file for the `model.obj`

    ### Adding metadata (`ACIT`)
    We use the circle mesh to do the reference points.
    Depending on the 3D model, there are specific information points you need to add see the [toolhead documentation](../developer-guide/toolheads.md).
    `ACIT` is the information to be parsed by Augmented Carpentry who uses them to derive all the essential information for fabrication process.
    The tool types for the `ACIT` are defined as a data class in the AC project [here](https://github.com/ibois-epfl/augmented-carpentry/blob/main/src/AIAC/ACInfoToolhead.h).

    Let's do the auger_drill_bit_20_235. The `ACIT` for "DrillBit" is defined in [here](https://github.com/ibois-epfl/augmented-carpentry/blob/c7748687f32cfd36dba3f54ec3434c64861d03d7/src/AIAC/ACInfoToolhead.h#L22). 
    ```cpp
            /// @brief name of the toolhead
            std::string NameACIT;
            /// @brief radius of the drillbit
            float RadiusACIT;

            /// @brief original position of the base of the toolhead
            glm::vec3 ToolbaseACIT;
            /// @brief original position of the tip of the toolhead
            glm::vec3 TooltipACIT;
            /// @brief original position of the tip of the toolhead eating the material
            glm::vec3 EattipACIT;
            /// @brief original position of the end of the drill chuck
            glm::vec3 ChucktipACIT;
    ```
    This accords with the final ACIT metadata of the auger_drill_bit_20_235.
    ```xml
    <acit version="0.1.0">
      <toolhead name="auger_drill_bit_20_235" type="drillbit">
        <toolbase> 0 0 0 </toolbase>
        <tooltip> 0 0 0.235 </tooltip>
        <eattip> 0 0 0.228 </eattip>
        <chucktip> 0 0 0.075 </chucktip>
        <radius> 0.02 </radius>
      </toolhead>
    </acit>
    ```

    To derive these information, we need `toolbase`, `tooltip`, `eattip`, `chucktip`, and `radius`.

    1. Open the [reformatter util](https://github.com/ibois-epfl/TTool/tree/main/util).
    2. Import the 3D model obj file to a new collection.
    ![import the model to the reformatter util](media/Adding-New-Drill-Bit---Toolhead/[3]1.add%20model)
    3. `toolbase` should be at `<0, 0, 0>`. `tooltip` is the length of the tool head from the base which from factory is 235mm. With these two reference points, we can align our model with the tip at `<0, 0, 0.235>`. The references points are represented by the circle mesh [Layout > Object Model > Add > Mesh > Circle], or you can just copy it from the other existing collection.
    ![placing the first two reference points](media/Adding-New-Drill-Bit---Toolhead/[3]adding%20tip%20and%20base.png)
    4. Adding the `eattip` and `chucktip`
    ![adding the eattip and chucktip](media/Adding-New-Drill-Bit---Toolhead/[3]chunk%20eat.png)
    5. Export the mesh of the tool in the collection individually as a new obj file [Select the model, then File > Export > Wavefront (obj), select "selection only" and name it to `model`]. This will be the final 3D model of the tool head which has the corresponding ACIT information.
    ![export the individual mesh](media/Adding-New-Drill-Bit---Toolhead/[3]model%20export.png)
    6. Create a new file named `metadata.acit` and copy the ACIT metadata to the file. Then, fill in the information you have derived in the "Object Property" > Transform > Location Z. Additionally, adding the `radius` of the tool head. This is the radius of the tool head. In this case, it is 0.02m.
    7. Create another file name 'model.initpose' and give it initial pose of the model. Be careful of the indentation and the spacing. This will be used for automatic "config.yml" generation of the [python script](https://github.com/ibois-epfl/TTool/blob/main/util/load_dataset_2_config.py).

    ![blender><](../assets/images/contribute/chunk%20eat.png){width="1000" class="rounded-corners"}

    ### Putting everything together
    Once everything is done, you should have:

    8. `model.obj` - 3D model that is re-scaled to the precise size of the physical tool head.
    9.  `model.mtl`<small>optional</small> - complimentary file for the model.obj
    10. `model_occlusion.jpg`<small>optional</small> - occlusion texture of the object from the 3D model reconstruction
    11. `model_normal.jpg`<small>optional</small> - occlusion texture of the object from the 3D model reconstruction
    12. `model.jpg`<small>optional</small> - diffuse map texture of the object from the 3D model reconstruction
    13. `metadata.acit` - xml formatted file with all the information crucial for the fabrication.
    14. `model.initpose` - you can copy paste any other `model.initpose` file. Just make sure to change the name of the model to the correct one.

    Put them to the file named by the tool head and _zip_ it.


## Dataset integration

The way your tool will be inserted in the AC dataset is by creating first an issue in the [issue tracker]. This will be used to discuss the model and its integration in the AC datasets. Once the model is validated, it will be added to the datasets by creating a [pull request].

  [issue tracker]: https://github.com/ibois-epfl/augmented-carpentry/issues
  [pull request]: making-a-pull-request.md

- [Add new tools or mounts](#add-new-tools-or-mounts)
  - [3D Model your items](#3d-model-your-items)
  - [Dataset integration](#dataset-integration)
    - [Title](#title)
    - [External link to downloadable data](#external-link-to-downloadable-data)
    - [Model data](#model-data)

### Title

A good title should be a short, one-sentence description of the issue, contain
all relevant information and, in particular, keywords to simplify the search in
our issue tracker.

| <!-- --> | Example  |
| -------- | -------- |
| :material-check:{ style="color: #4DB6AC" } __Clear__ | Clarify social cards setup on Windows
| :material-close:{ style="color: #EF5350" } __Unclear__ | Missing information in the docs
| :material-close:{ style="color: #EF5350" } __Useless__ | Help

### External link to downloadable data

Include a link to the 3D model and its data of the toolhead or mount as a `.zip` file. This will be used to validate the model and its integration in the AC datasets.

> __Why we need this__: providing an external link to the 3D model and its data will help us understand the model and its integration in the AC datasets without overloading the github repository.

### Model data

Provide a the toolhead or mount model. Possibly with links to existing references from brands.

> __Why we need this__: describing the model clearly, with references and data is a prerequisite for improving AC's dataset – we need to understand what's available and what's missing, maybe your tool already exists.
