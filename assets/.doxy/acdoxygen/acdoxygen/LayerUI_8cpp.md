

# File LayerUI.cpp



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**LayerUI.cpp**](LayerUI_8cpp.md)

[Go to the source code of this file](LayerUI_8cpp_source.md)



* `#include "aiacpch.h"`
* `#include "AIAC/LayerUI.h"`
* `#include "AIAC/Application.h"`
* `#include "AIAC/Image.h"`
* `#include "AIAC/Render/Renderer.h"`
* `#include "AIAC/UI/ImGuiFileDialog.h"`
* `#include "AIAC/UI/ClrPalette.h"`
* `#include "AIAC/UI/CustomLogos.h"`
* `#include "LayerCameraCalib.h"`
* `#include "LayerLogRecorder.h"`
* `#include "ttool.hh"`
* `#include "utils/utils.h"`
* `#include "LayerUtils.h"`
* `#include <filesystem>`
* `#include <optional>`
* `#include <string>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |
























## Public Functions

| Type | Name |
| ---: | :--- |
|  std::optional&lt; std::string &gt; | [**GetLatestFilePath**](#function-getlatestfilepath) (const std::string & directoryPath, const std::string & extension) <br> |




























## Public Functions Documentation




### function GetLatestFilePath 

```C++
std::optional< std::string > GetLatestFilePath (
    const std::string & directoryPath,
    const std::string & extension
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerUI.cpp`

