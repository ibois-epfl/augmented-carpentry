

# Class AIAC::TimberInfo::Hole



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md) **>** [**Hole**](classAIAC_1_1TimberInfo_1_1Hole.md)








Inherits the following classes: [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)
























## Public Attributes inherited from AIAC::TimberInfo::Component

See [AIAC::TimberInfo::Component](classAIAC_1_1TimberInfo_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  bool | [**IsMarkedDone**](classAIAC_1_1TimberInfo_1_1Component.md#variable-ismarkeddone)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
| virtual glm::vec3 | [**GetCenter**](#function-getcenter) () override const<br>[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._ |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**GetEndPointGO**](#function-getendpointgo) () <br> |
|  \_\_always\_inline double | [**GetRadius**](#function-getradius) () const<br> |
|  \_\_always\_inline std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**GetStartPointGO**](#function-getstartpointgo) () <br> |
|   | [**Hole**](#function-hole) () <br> |
| virtual void | [**SetAsCurrent**](#function-setascurrent) () <br>_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __ |
| virtual void | [**SetAsDone**](#function-setasdone) () <br> |
| virtual void | [**SetAsNotDone**](#function-setasnotdone) () <br> |
| virtual void | [**SetVisibility**](#function-setvisibility) (bool visible) <br>[_**Cut**_](classAIAC_1_1TimberInfo_1_1Cut.md) _._ |
|  void | [**SwapStartEnd**](#function-swapstartend) () <br> |


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




### function GetCenter 

[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._
```C++
inline virtual glm::vec3 AIAC::TimberInfo::Hole::GetCenter () override const
```



Implements [*AIAC::TimberInfo::Component::GetCenter*](classAIAC_1_1TimberInfo_1_1Component.md#function-getcenter)


<hr>



### function GetEndPointGO 

```C++
inline std::shared_ptr< GOPoint > AIAC::TimberInfo::Hole::GetEndPointGO () 
```




<hr>



### function GetRadius 

```C++
inline __always_inline double AIAC::TimberInfo::Hole::GetRadius () const
```




<hr>



### function GetStartPointGO 

```C++
inline __always_inline std::shared_ptr< GOPoint > AIAC::TimberInfo::Hole::GetStartPointGO () 
```




<hr>



### function Hole 

```C++
inline AIAC::TimberInfo::Hole::Hole () 
```




<hr>



### function SetAsCurrent 

_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __
```C++
virtual void AIAC::TimberInfo::Hole::SetAsCurrent () 
```



Implements [*AIAC::TimberInfo::Component::SetAsCurrent*](classAIAC_1_1TimberInfo_1_1Component.md#function-setascurrent)


<hr>



### function SetAsDone 

```C++
virtual void AIAC::TimberInfo::Hole::SetAsDone () 
```



Implements [*AIAC::TimberInfo::Component::SetAsDone*](classAIAC_1_1TimberInfo_1_1Component.md#function-setasdone)


<hr>



### function SetAsNotDone 

```C++
virtual void AIAC::TimberInfo::Hole::SetAsNotDone () 
```



Implements [*AIAC::TimberInfo::Component::SetAsNotDone*](classAIAC_1_1TimberInfo_1_1Component.md#function-setasnotdone)


<hr>



### function SetVisibility 

[_**Cut**_](classAIAC_1_1TimberInfo_1_1Cut.md) _._
```C++
virtual void AIAC::TimberInfo::Hole::SetVisibility (
    bool visible
) 
```



Implements [*AIAC::TimberInfo::Component::SetVisibility*](classAIAC_1_1TimberInfo_1_1Component.md#function-setvisibility)


<hr>



### function SwapStartEnd 

```C++
void AIAC::TimberInfo::Hole::SwapStartEnd () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

