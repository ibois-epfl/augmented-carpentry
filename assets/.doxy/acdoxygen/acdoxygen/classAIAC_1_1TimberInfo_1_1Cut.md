

# Class AIAC::TimberInfo::Cut



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md) **>** [**Cut**](classAIAC_1_1TimberInfo_1_1Cut.md)








Inherits the following classes: [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)












## Classes

| Type | Name |
| ---: | :--- |
| class | [**Edge**](classAIAC_1_1TimberInfo_1_1Cut_1_1Edge.md) <br> |
| class | [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) <br> |












## Public Attributes inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  bool | [**IsMarkedDone**](classAIAC_1_1TimberInfo_1_1Component.md#variable-ismarkeddone)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Cut**](#function-cut) () <br> |
|  std::map&lt; std::string, [**Edge**](classAIAC_1_1TimberInfo_1_1Cut_1_1Edge.md) &gt; & | [**GetAllEdges**](#function-getalledges) () <br> |
|  std::map&lt; std::string, [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) &gt; & | [**GetAllFaces**](#function-getallfaces) () <br> |
|  std::set&lt; std::string &gt; & | [**GetAllNonExposedEdgeIDs**](#function-getallnonexposededgeids) () <br> |
|  std::set&lt; std::string &gt; & | [**GetAllNonExposedFaceIDs**](#function-getallnonexposedfaceids) () <br> |
| virtual glm::vec3 | [**GetCenter**](#function-getcenter) () override const<br>[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._ |
|  [**Edge**](classAIAC_1_1TimberInfo_1_1Cut_1_1Edge.md) & | [**GetEdge**](#function-getedge) (std::string id) <br> |
|  [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) & | [**GetFace**](#function-getface) (std::string id) <br> |
|  std::map&lt; std::string, [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) &gt; | [**GetFaceNeighbors**](#function-getfaceneighbors) (std::string faceID) <br> |
|  [**TimberInfo::Cut::Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) | [**GetHighlightedFace**](#function-gethighlightedface) () <br> |
|  std::string | [**GetHighlightedFaceID**](#function-gethighlightedfaceid) () const<br> |
|  std::map&lt; std::string, [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md) &gt; | [**GetHighlightedFaceNeighbors**](#function-gethighlightedfaceneighbors) () <br> |
|  void | [**HighlightFace**](#function-highlightface) (const std::string & faceId, glm::vec4 color=glm::vec4(0)) <br> |
|  bool | [**IsSingleFace**](#function-issingleface) () const<br> |
| virtual void | [**SetAsCurrent**](#function-setascurrent) () <br>_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __ |
| virtual void | [**SetAsDone**](#function-setasdone) () <br> |
| virtual void | [**SetAsNotDone**](#function-setasnotdone) () <br> |
| virtual void | [**SetVisibility**](#function-setvisibility) (bool visible) <br> |
|  void | [**SetVisibilityAllCotas**](#function-setvisibilityallcotas) (bool visible) <br> |


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




### function Cut 

```C++
inline AIAC::TimberInfo::Cut::Cut () 
```




<hr>



### function GetAllEdges 

```C++
inline std::map< std::string, Edge > & AIAC::TimberInfo::Cut::GetAllEdges () 
```




<hr>



### function GetAllFaces 

```C++
inline std::map< std::string, Face > & AIAC::TimberInfo::Cut::GetAllFaces () 
```




<hr>



### function GetAllNonExposedEdgeIDs 

```C++
inline std::set< std::string > & AIAC::TimberInfo::Cut::GetAllNonExposedEdgeIDs () 
```




<hr>



### function GetAllNonExposedFaceIDs 

```C++
inline std::set< std::string > & AIAC::TimberInfo::Cut::GetAllNonExposedFaceIDs () 
```




<hr>



### function GetCenter 

[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._
```C++
inline virtual glm::vec3 AIAC::TimberInfo::Cut::GetCenter () override const
```



Implements [*AIAC::TimberInfo::Component::GetCenter*](classAIAC_1_1TimberInfo_1_1Component.md#function-getcenter)


<hr>



### function GetEdge 

```C++
inline Edge & AIAC::TimberInfo::Cut::GetEdge (
    std::string id
) 
```




<hr>



### function GetFace 

```C++
inline Face & AIAC::TimberInfo::Cut::GetFace (
    std::string id
) 
```




<hr>



### function GetFaceNeighbors 

```C++
inline std::map< std::string, Face > AIAC::TimberInfo::Cut::GetFaceNeighbors (
    std::string faceID
) 
```




<hr>



### function GetHighlightedFace 

```C++
inline TimberInfo::Cut::Face AIAC::TimberInfo::Cut::GetHighlightedFace () 
```




<hr>



### function GetHighlightedFaceID 

```C++
inline std::string AIAC::TimberInfo::Cut::GetHighlightedFaceID () const
```




<hr>



### function GetHighlightedFaceNeighbors 

```C++
inline std::map< std::string, Face > AIAC::TimberInfo::Cut::GetHighlightedFaceNeighbors () 
```




<hr>



### function HighlightFace 

```C++
void AIAC::TimberInfo::Cut::HighlightFace (
    const std::string & faceId,
    glm::vec4 color=glm::vec4(0)
) 
```




<hr>



### function IsSingleFace 

```C++
inline bool AIAC::TimberInfo::Cut::IsSingleFace () const
```




<hr>



### function SetAsCurrent 

_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __
```C++
virtual void AIAC::TimberInfo::Cut::SetAsCurrent () 
```



Implements [*AIAC::TimberInfo::Component::SetAsCurrent*](classAIAC_1_1TimberInfo_1_1Component.md#function-setascurrent)


<hr>



### function SetAsDone 

```C++
virtual void AIAC::TimberInfo::Cut::SetAsDone () 
```



Implements [*AIAC::TimberInfo::Component::SetAsDone*](classAIAC_1_1TimberInfo_1_1Component.md#function-setasdone)


<hr>



### function SetAsNotDone 

```C++
virtual void AIAC::TimberInfo::Cut::SetAsNotDone () 
```



Implements [*AIAC::TimberInfo::Component::SetAsNotDone*](classAIAC_1_1TimberInfo_1_1Component.md#function-setasnotdone)


<hr>



### function SetVisibility 

```C++
virtual void AIAC::TimberInfo::Cut::SetVisibility (
    bool visible
) 
```



Implements [*AIAC::TimberInfo::Component::SetVisibility*](classAIAC_1_1TimberInfo_1_1Component.md#function-setvisibility)


<hr>



### function SetVisibilityAllCotas 

```C++
inline void AIAC::TimberInfo::Cut::SetVisibilityAllCotas (
    bool visible
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

