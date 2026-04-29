

# File FabFeedback.h



[**FileList**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Feedback**](dir_2e808e595a766fe55342199a604574e7.md) **>** [**FabFeedback.h**](FabFeedback_8h.md)

[Go to the source code of this file](FabFeedback_8h_source.md)



* `#include "AIAC/Config.h"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**AIAC**](namespaceAIAC.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**FabFeedback**](classAIAC_1_1FabFeedback.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**AC\_FF\_COMP**](FabFeedback_8h.md#define-ac_ff_comp)  `AIAC\_APP.GetLayer&lt;LayerModel&gt;()-&gt;GetACInfoModel().GetTimberInfo().GetCurrentComponent()`<br> |
| define  | [**AC\_FF\_TOOL**](FabFeedback_8h.md#define-ac_ff_tool)  `AIAC\_APP.GetLayer&lt;LayerToolhead&gt;()-&gt;ACInfoToolheadManager-&gt;GetActiveToolhead()`<br> |

## Macro Definition Documentation





### define AC\_FF\_COMP 

```C++
#define AC_FF_COMP `AIAC_APP.GetLayer<LayerModel>()->GetACInfoModel().GetTimberInfo().GetCurrentComponent()`
```




<hr>



### define AC\_FF\_TOOL 

```C++
#define AC_FF_TOOL `AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolhead()`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/FabFeedback.h`

