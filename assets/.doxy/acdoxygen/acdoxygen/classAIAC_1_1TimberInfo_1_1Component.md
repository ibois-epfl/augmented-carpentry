

# Class AIAC::TimberInfo::Component



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md) **>** [**Component**](classAIAC_1_1TimberInfo_1_1Component.md)










Inherited by the following classes: [AIAC::TimberInfo::Cut](classAIAC_1_1TimberInfo_1_1Cut.md),  [AIAC::TimberInfo::Cut::Edge](classAIAC_1_1TimberInfo_1_1Cut_1_1Edge.md),  [AIAC::TimberInfo::Cut::Face](classAIAC_1_1TimberInfo_1_1Cut_1_1Face.md),  [AIAC::TimberInfo::Hole](classAIAC_1_1TimberInfo_1_1Hole.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**IsMarkedDone**](#variable-ismarkeddone)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Component**](#function-component) (std::string type) <br> |
| virtual glm::vec3 | [**GetCenter**](#function-getcenter) () const<br>[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._ |
|  \_\_always\_inline std::string | [**GetTypeString**](#function-gettypestring) () const<br> |
| virtual void | [**SetAsCurrent**](#function-setascurrent) () <br>_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __ |
| virtual void | [**SetAsDone**](#function-setasdone) () <br> |
| virtual void | [**SetAsNotDone**](#function-setasnotdone) () <br> |
| virtual void | [**SetVisibility**](#function-setvisibility) (bool visible) <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  pugi::xml\_node | [**m\_ACIMDocNode**](#variable-m_acimdocnode)  <br> |
|  glm::vec3 | [**m\_Center**](#variable-m_center)  <br> |
|  std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; | [**m\_GOPrimitives**](#variable-m_goprimitives)  <br> |
|  std::string | [**m\_ID**](#variable-m_id)  <br> |
|  float | [**m\_Scale**](#variable-m_scale)  <br> |
|  ACIMState | [**m\_State**](#variable-m_state)  <br> |
|  std::string | [**m\_Type**](#variable-m_type)  <br> |




















## Public Attributes Documentation




### variable IsMarkedDone 

```C++
bool AIAC::TimberInfo::Component::IsMarkedDone;
```




<hr>
## Public Functions Documentation




### function Component 

```C++
inline AIAC::TimberInfo::Component::Component (
    std::string type
) 
```




<hr>



### function GetCenter 

[_**Hole**_](classAIAC_1_1TimberInfo_1_1Hole.md) _._
```C++
virtual glm::vec3 AIAC::TimberInfo::Component::GetCenter () const
```




<hr>



### function GetTypeString 

```C++
inline __always_inline std::string AIAC::TimberInfo::Component::GetTypeString () const
```




<hr>



### function SetAsCurrent 

_&lt; Base_ [_**Component**_](classAIAC_1_1TimberInfo_1_1Component.md) __
```C++
virtual void AIAC::TimberInfo::Component::SetAsCurrent () 
```




<hr>



### function SetAsDone 

```C++
virtual void AIAC::TimberInfo::Component::SetAsDone () 
```




<hr>



### function SetAsNotDone 

```C++
virtual void AIAC::TimberInfo::Component::SetAsNotDone () 
```




<hr>



### function SetVisibility 

```C++
virtual void AIAC::TimberInfo::Component::SetVisibility (
    bool visible
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_ACIMDocNode 

```C++
pugi::xml_node AIAC::TimberInfo::Component::m_ACIMDocNode;
```




<hr>



### variable m\_Center 

```C++
glm::vec3 AIAC::TimberInfo::Component::m_Center;
```




<hr>



### variable m\_GOPrimitives 

```C++
std::vector<std::shared_ptr<GOPrimitive> > AIAC::TimberInfo::Component::m_GOPrimitives;
```




<hr>



### variable m\_ID 

```C++
std::string AIAC::TimberInfo::Component::m_ID;
```




<hr>



### variable m\_Scale 

```C++
float AIAC::TimberInfo::Component::m_Scale;
```




<hr>



### variable m\_State 

```C++
ACIMState AIAC::TimberInfo::Component::m_State;
```




<hr>



### variable m\_Type 

```C++
std::string AIAC::TimberInfo::Component::m_Type;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

