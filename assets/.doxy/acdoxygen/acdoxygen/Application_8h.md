

# File Application.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Application.h**](Application_8h.md)

[Go to the source code of this file](Application_8h_source.md)



* `#include "AIAC/Camera.h"`
* `#include "AIAC/Render/Renderer.h"`
* `#include "AIAC/Assert.h"`
* `#include "AIAC/Window.h"`
* `#include "AIAC/Layer.h"`
* `#include "AIAC/LayerSlam.h"`
* `#include "AIAC/LayerCamera.h"`
* `#include "AIAC/LayerModel.h"`
* `#include "AIAC/LayerToolhead.h"`
* `#include "AIAC/LayerFeedback.h"`
* `#include "AIAC/EventSys/EventBus.h"`
* `#include "AIAC/GOSys/GO.h"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Application**](classAIAC_1_1Application.md) <br> |
| struct | [**ApplicationSpecification**](structAIAC_1_1ApplicationSpecification.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**AIAC\_APP**](Application_8h.md#define-aiac_app)  `AIAC::Application::GetInstance()`<br> |
| define  | [**AIAC\_EBUS**](Application_8h.md#define-aiac_ebus)  `AIAC\_APP.GetEventBus()`<br> |
| define  | [**AIAC\_GOREG**](Application_8h.md#define-aiac_goreg)  `AIAC\_APP.GetGORegistry()`<br> |

## Macro Definition Documentation





### define AIAC\_APP 

```C++
#define AIAC_APP `AIAC::Application::GetInstance()`
```




<hr>



### define AIAC\_EBUS 

```C++
#define AIAC_EBUS `AIAC_APP.GetEventBus()`
```




<hr>



### define AIAC\_GOREG 

```C++
#define AIAC_GOREG `AIAC_APP.GetGORegistry()`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Application.h`

