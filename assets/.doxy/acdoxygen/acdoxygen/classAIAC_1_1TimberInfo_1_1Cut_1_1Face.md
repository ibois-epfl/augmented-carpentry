

# Class AIAC::TimberInfo::Cut::Face



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md) **>** [**Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) **>** [**Face**](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md)








Inherits the following classes: [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)
























## Public Attributes inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  bool | [**IsMarkedDone**](classAIAC_1_1TimberInfo_1_1Component.md#variable-ismarkeddone)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Face**](#function-face) () <br> |
| virtual glm::vec3 | [**GetCenter**](#function-getcenter) () override const<br>[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._ |
|  std::vector&lt; glm::vec3 &gt; | [**GetCorners**](#function-getcorners) () const<br> |
|  std::set&lt; std::string &gt; | [**GetEdges**](#function-getedges) () const<br> |
|  std::set&lt; std::string &gt; | [**GetNeighbors**](#function-getneighbors) () const<br> |
|  glm::vec3 | [**GetNormal**](#function-getnormal) () const<br> |
|  bool | [**IsExposed**](#function-isexposed) () const<br> |


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




### function Face 

```C++
inline AIAC::TimberInfo::Cut::Face::Face () 
```




<hr>



### function GetCenter 

[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._
```C++
inline virtual glm::vec3 AIAC::TimberInfo::Cut::Face::GetCenter () override const
```



Implements [*AIAC::TimberInfo::Component::GetCenter*](classAIAC_1_1TimberInfo_1_1Component.md#function-getcenter)


<hr>



### function GetCorners 

```C++
inline std::vector< glm::vec3 > AIAC::TimberInfo::Cut::Face::GetCorners () const
```




<hr>



### function GetEdges 

```C++
inline std::set< std::string > AIAC::TimberInfo::Cut::Face::GetEdges () const
```




<hr>



### function GetNeighbors 

```C++
inline std::set< std::string > AIAC::TimberInfo::Cut::Face::GetNeighbors () const
```




<hr>



### function GetNormal 

```C++
inline glm::vec3 AIAC::TimberInfo::Cut::Face::GetNormal () const
```




<hr>



### function IsExposed 

```C++
inline bool AIAC::TimberInfo::Cut::Face::IsExposed () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

