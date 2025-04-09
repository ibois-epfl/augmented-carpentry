

# Class AIAC::TimberInfo::Cut::Edge



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md) **>** [**Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) **>** [**Edge**](classAIAC_1_1TimberInfo_1_1Cut_1_1Edge.md)








Inherits the following classes: [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)
























## Public Attributes inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  bool | [**IsMarkedDone**](classAIAC_1_1TimberInfo_1_1Component.md#variable-ismarkeddone)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearCotas**](#function-clearcotas) () <br>_Clear the cotas._  |
|   | [**Edge**](#function-edge) () <br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetEndPt**](#function-getendpt) () <br> |
|  [**GOPoint**](classAIAC_1_1GOPoint.md) | [**GetStartPt**](#function-getstartpt) () <br> |
|  void | [**SetCotasVisibility**](#function-setcotasvisibility) (bool visible) <br>_Set the Cotas Visibility object._  |


## Public Functions inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|   | [**Component**](classAIAC_1_1TimberInfo_1_1Component.md#function-component) (std::string type) <br> |
| virtual glm::vec3 | [**GetCenter**](classAIAC_1_1TimberInfo_1_1Component.md#function-getcenter) () const<br>[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._ |
|  \_\_always\_inline std::string | [**GetTypeString**](classAIAC_1_1TimberInfo_1_1Component.md#function-gettypestring) () const<br> |
| virtual void | [**SetAsCurrent**](classAIAC_1_1TimberInfo_1_1Component.md#function-setascurrent) () <br>_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __ |
| virtual void | [**SetAsDone**](classAIAC_1_1TimberInfo_1_1Component.md#function-setasdone) () <br> |
| virtual void | [**SetAsNotDone**](classAIAC_1_1TimberInfo_1_1Component.md#function-setasnotdone) () <br> |
| virtual void | [**SetVisibility**](classAIAC_1_1TimberInfo_1_1Component.md#function-setvisibility) (bool visible) <br> |
















## Protected Attributes inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  pugi::xml\_node | [**m\_ACIMDocNode**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_acimdocnode)  <br> |
|  glm::vec3 | [**m\_Center**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_center)  <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_GOPrimitives**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_goprimitives)  <br> |
|  std::string | [**m\_ID**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_id)  <br> |
|  float | [**m\_Scale**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_scale)  <br> |
|  ACIMState | [**m\_State**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_state)  <br> |
|  std::string | [**m\_Type**](classAIAC_1_1TimberInfo_1_1Component.md#variable-m_type)  <br> |






































## Public Functions Documentation




### function ClearCotas 

_Clear the cotas._ 
```C++
inline void AIAC::TimberInfo::Cut::Edge::ClearCotas () 
```




<hr>



### function Edge 

```C++
inline AIAC::TimberInfo::Cut::Edge::Edge () 
```




<hr>



### function GetEndPt 

```C++
inline GOPoint AIAC::TimberInfo::Cut::Edge::GetEndPt () 
```




<hr>



### function GetStartPt 

```C++
inline GOPoint AIAC::TimberInfo::Cut::Edge::GetStartPt () 
```




<hr>



### function SetCotasVisibility 

_Set the Cotas Visibility object._ 
```C++
inline void AIAC::TimberInfo::Cut::Edge::SetCotasVisibility (
    bool visible
) 
```





**Parameters:**


* `visible` if true, the cotas will be visible 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

