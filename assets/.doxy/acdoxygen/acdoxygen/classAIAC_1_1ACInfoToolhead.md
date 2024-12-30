

# Class AIAC::ACInfoToolhead



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ACInfoToolhead**](classAIAC_1_1ACInfoToolhead.md)



_the class holding the information of the toolhead (GOs, metadata, etc)_ 

* `#include <ACInfoToolhead.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ACInfoToolhead**](#function-acinfotoolhead-12) () = default<br> |
|   | [**ACInfoToolhead**](#function-acinfotoolhead-22) (std::string acitPath, std::string meshObjPath, int id) <br> |
|  void | [**AddGOsInfo**](#function-addgosinfo) ([**ToolHeadData**](classAIAC_1_1ToolHeadData.md) & data) <br>_From the parse data acit, create the corresponding geometries (e.g._ [_**GOPoint**_](classAIAC_1_1GOPoint.md) _for tooltip, toolbase, etc)_ |
|  void | [**AddGOsInfoChainSaw**](#function-addgosinfochainsaw) ([**ToolHeadData**](classAIAC_1_1ToolHeadData.md) & data) <br> |
|  void | [**AddGOsInfoCircularSaw**](#function-addgosinfocircularsaw) ([**ToolHeadData**](classAIAC_1_1ToolHeadData.md) & data) <br> |
|  void | [**AddGOsInfoDrillBit**](#function-addgosinfodrillbit) ([**ToolHeadData**](classAIAC_1_1ToolHeadData.md) & data) <br> |
|  void | [**AddGOsInfoSaberSaw**](#function-addgosinfosabersaw) ([**ToolHeadData**](classAIAC_1_1ToolHeadData.md) & data) <br> |
|  void | [**CopyGOsInfoOriginal**](#function-copygosinfooriginal) () <br>_copy the original transform of the GO infos_  |
|  T | [**GetData**](#function-getdata) () const<br>_access the data of the toolheads_  |
|  int | [**GetId**](#function-getid) () const<br>_Get the id of the toolhead._  |
|  std::string | [**GetName**](#function-getname) () const<br>_Get the name of the toolhead._  |
|  \_\_always\_inline ACToolHeadType | [**GetType**](#function-gettype) () const<br>_Retrieve the type of the toolhead._  |
|  std::string | [**GetTypeString**](#function-gettypestring) () const<br>_Retrieve the type of the toolhead as a string._  |
|  void | [**SetVisibility**](#function-setvisibility) (bool visible) <br>_Set the visibility of the geometries and widgets of the toolhead._  |
|  \_\_always\_inline std::string | [**ToString**](#function-tostring) () const<br>_convert to a string byy getting the name_  |
|  void | [**Transform**](#function-transform) (glm::mat4 transform) <br>_transform all the geometries, widgets and mesh contained in the_ [_**ACInfoToolhead**_](classAIAC_1_1ACInfoToolhead.md) _object_ |
|  void | [**TransformGO**](#function-transformgo) (std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; goPtr, std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; goOriginalPtr, glm::mat4 transform) <br>_transform a specific geometry_  |
|  void | [**TransformSync**](#function-transformsync) () <br>_rotate around local x axis of the toolhead 90 degrees to match the AC coordinate system with the TTool coordinate system Should only be called once at loading time_  |




























## Public Functions Documentation




### function ACInfoToolhead [1/2]

```C++
AIAC::ACInfoToolhead::ACInfoToolhead () = default
```




<hr>



### function ACInfoToolhead [2/2]

```C++
AIAC::ACInfoToolhead::ACInfoToolhead (
    std::string acitPath,
    std::string meshObjPath,
    int id
) 
```




<hr>



### function AddGOsInfo 

_From the parse data acit, create the corresponding geometries (e.g._ [_**GOPoint**_](classAIAC_1_1GOPoint.md) _for tooltip, toolbase, etc)_
```C++
void AIAC::ACInfoToolhead::AddGOsInfo (
    ToolHeadData & data
) 
```




<hr>



### function AddGOsInfoChainSaw 

```C++
void AIAC::ACInfoToolhead::AddGOsInfoChainSaw (
    ToolHeadData & data
) 
```




<hr>



### function AddGOsInfoCircularSaw 

```C++
void AIAC::ACInfoToolhead::AddGOsInfoCircularSaw (
    ToolHeadData & data
) 
```




<hr>



### function AddGOsInfoDrillBit 

```C++
void AIAC::ACInfoToolhead::AddGOsInfoDrillBit (
    ToolHeadData & data
) 
```




<hr>



### function AddGOsInfoSaberSaw 

```C++
void AIAC::ACInfoToolhead::AddGOsInfoSaberSaw (
    ToolHeadData & data
) 
```




<hr>



### function CopyGOsInfoOriginal 

_copy the original transform of the GO infos_ 
```C++
void AIAC::ACInfoToolhead::CopyGOsInfoOriginal () 
```




<hr>



### function GetData 

_access the data of the toolheads_ 
```C++
template<typename T>
inline T AIAC::ACInfoToolhead::GetData () const
```




<hr>



### function GetId 

_Get the id of the toolhead._ 
```C++
inline int AIAC::ACInfoToolhead::GetId () const
```




<hr>



### function GetName 

_Get the name of the toolhead._ 
```C++
inline std::string AIAC::ACInfoToolhead::GetName () const
```




<hr>



### function GetType 

_Retrieve the type of the toolhead._ 
```C++
inline __always_inline ACToolHeadType AIAC::ACInfoToolhead::GetType () const
```




<hr>



### function GetTypeString 

_Retrieve the type of the toolhead as a string._ 
```C++
inline std::string AIAC::ACInfoToolhead::GetTypeString () const
```




<hr>



### function SetVisibility 

_Set the visibility of the geometries and widgets of the toolhead._ 
```C++
void AIAC::ACInfoToolhead::SetVisibility (
    bool visible
) 
```




<hr>



### function ToString 

_convert to a string byy getting the name_ 
```C++
inline __always_inline std::string AIAC::ACInfoToolhead::ToString () const
```




<hr>



### function Transform 

_transform all the geometries, widgets and mesh contained in the_ [_**ACInfoToolhead**_](classAIAC_1_1ACInfoToolhead.md) _object_
```C++
void AIAC::ACInfoToolhead::Transform (
    glm::mat4 transform
) 
```




<hr>



### function TransformGO 

_transform a specific geometry_ 
```C++
void AIAC::ACInfoToolhead::TransformGO (
    std::shared_ptr< GOPrimitive > goPtr,
    std::shared_ptr< GOPrimitive > goOriginalPtr,
    glm::mat4 transform
) 
```




<hr>



### function TransformSync 

_rotate around local x axis of the toolhead 90 degrees to match the AC coordinate system with the TTool coordinate system Should only be called once at loading time_ 
```C++
void AIAC::ACInfoToolhead::TransformSync () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoToolhead.h`

