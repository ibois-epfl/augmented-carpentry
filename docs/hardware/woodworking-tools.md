
# Woodworking tools

/// html | div[style='float: left; width: 52%;']

![view of the camera used](../assets/images/getting_started/tool_top.JPG){width="600" class="rounded-corners"}

///

/// html | div[style='float: right;width: 45%;']

AC is designed to seamlessly integrate with virtually any woodworking tool, new or old, provided you can:

- [x] securely mount the AC camera and display unit onto the tool itself
- [x] having a 3D model digital twin of the tool head you want to use

For the first one we provide a set of 3D printable mounts that you can download and print.

For the second one, you can find a list of the available toolheads [here](https://zenodo.org/records/12578820) that we already have in our database.

If you want to add your own 3d-printable mount or tool head model and share it with the community, follow the instructions in the section [contributing](../contributing/index.md).

///

/// html | div[style='clear: both;']
///

<!-- TODO: add drawing axo of the system of the mount on the tool with locline and camera and screen -->



## Available Toolheads

/// html | div[style='float: left; width: 52%;']

The following is a list of the available toolheads that are already integrated into the AC system. You will need to use or acquire the corresponding physical toolhead to use the AC system. Each toolhead is digitize and integrated to the dataset, the digital model is necessary to allow AC to detect the 3D position of the toolhead from the sensor stream. The Zenodo repository containing the dataset is [here](https://zenodo.org/records/12578820).

!!! note "Toolhead integration"
    If you want to know more about the details of the integration and how toolhead are managed in the AC system, you can read the [developer guide](../developer-guide/toolheads.md).

!!! tip "Want to add a new toolhead?"
    If you want to add your own toolhead to the AC system, follow the instructions in the section [contributing](../contributing/index.md).

///

/// html | div[style='float: right;width: 45%;']

![rotating model drill bit](../assets/images/getting_started/drill_anim.gif){width="500" class="rounded-corners"}

///

/// html | div[style='clear: both;']
///


{{ run_python_script('docs/scripts/get_zenodo_toolheads.py') }}

## Available 3D mounts

<div class="grid" markdown>
![](../assets/images/getting_started/hardware_mounts/animation_mount_1.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_2.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/mount_ex_3.png){width="210"} ![](../assets/images/getting_started/hardware_mounts/mount_ex_4.png){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_9.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_5.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/mount_ex_6.png){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_7.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_8.gif){width="210"} ![](../assets/images/getting_started/hardware_mounts/animation_mount_10.gif){width="210"}
</div>

Each mount is designed with a flexible integration mechanism, allowing for the attachment of various clipping solutions. Our reference implementation utilizes magnetic clips and a loc-line arm to ensure secure, tool-safe mounting of the sensors and interfaces and easy removal. However, the design files allow users to incorporate their preferred fastening methods—ranging from simple clips to more complex spring-loaded solutions—enabling adaptation to a broad range of tool geometries.
 
- Identify the corresponding mount file that matches your tool brand and model.
- Download and 3D print the STL file(s).
- Integrate your desired clipping mechanism.
- Attach the completed mount to your woodworking tool.

The Zenodo repository containing the dataset is [here](https://zenodo.org/records/14531724).

!!! tip "Want to add a new mount?"
    If you want to add your own toolhead to the AC system, follow the instructions in the section [contributing](../contributing/index.md).

{{ run_python_script('docs/scripts/get_zenodo_mounts.py') }}


## Components list

!!! print-parts "Parts"

    ![><>](../assets/images/getting_started/hard_detail_mount.png){width=500}

    Here's the list of the parts you will need to obtain or realize for this section:

    - [x] &nbsp;&nbsp; electric woodworking tool
    - [x] &nbsp;&nbsp; (**C**) 3D-printed mount compatible with the tool
    - [x] &nbsp;&nbsp; (**D**) digitized toolhead
    - [x] &nbsp;&nbsp; (**B**) clipping mechanism to interchange the camera and interface quickly from tool to tool
    - [x] &nbsp;&nbsp; (**A**) metal magnet-clipping plate ([:octicons-file-code-16: `assets/hardware_parts/mount/metal_magnet_slot.pdf`](https://github.com/ibois-epfl/augmented-carpentry/blob/main/assets/hardware_parts/mount/metal_magnet_slot.pdf))
    - [ ] lock-line adaptor for magnet-clipping plate