
# Tools

<!-- AC is designed to be *machine independent*, it is only dependent on the toolheads (e.g.: drill bits, circular saw blades and chainsaw boards). You can find a list of the available toolheads [here](https://zenodo.org/records/12578820). If you want to add your own, open a Pull Request to the repo [TTool](https://github.com/ibois-epfl/TTool) and follow the [Wiki](https://github.com/ibois-epfl/TTool/wiki). -->

/// html | div[style='float: left; width: 52%;']

![view of the camera used](../assets/images/getting_started/tool_top.JPG){width="600" class="rounded-corners"}

///

/// html | div[style='float: right;width: 45%;']

<!-- TODO: rearrange better this intro -->

AC is designed to seamlessly integrate with virtually any woodworking tool, new or old, provided you can:

- [x] securely mount the AC camera and display unit onto the tool itself
- [x] having a 3D model digital twin of the tool head you want to use

For the first one we provide a set of 3D printable mounts that you can download and print.

For the second one, you can find a list of the available toolheads [here](https://zenodo.org/records/12578820) that we already have in our database.

If you want to add your own 3d-printable mount or tool head model and share it with the community, follow the instructions in the section [contributing](../contributing/index.md).

///

/// html | div[style='clear: both;']
///



## Tool mounts

<!-- TODO: make a split tab: existing dataset VS add new -->

The camera and the display needs to be mounted on the tool itself and follow its movement. To do so we share here the system we designed for our current prototype. You can download

{{ run_python_script('docs/scripts/get_zenodo_toolheads.py') }}


## Tool heads dataset

<!-- TODO: make a split tab: existing dataset VS add new -->
<!-- TODO: try to add a macros mkdocs to autogenerate the table -->


AC is designed to be *machine independent*, meaning that it is only dependent on the toolheads (e.g.: drill bits, circular saw blades and chainsaw boards). This means that you can attach any toolhead to the machine and the system will adapt to it if the toolhead is in the list of those integrated in AC.

You can find a list of the available toolheads already available here [here](https://zenodo.org/records/12578820). If you want to add your own and share it with the community, follow the 

<!-- TODO: update -->
## Components list

!!! print-parts "Parts"

    Here's the list of the parts you will need to obtain or realize for this section:

    - [x] &nbsp;&nbsp; Machines with available mounts
    - [x] &nbsp;&nbsp; *3D print the downloaded mounts*
    - [x] &nbsp;&nbsp; Tool heads present in the model database