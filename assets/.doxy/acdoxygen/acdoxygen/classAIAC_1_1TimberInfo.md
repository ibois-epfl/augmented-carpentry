

# Class AIAC::TimberInfo



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**TimberInfo**](classAIAC_1_1TimberInfo.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Component**](classAIAC_1_1TimberInfo_1_1Component.md) <br> |
| class | [**Cut**](classAIAC_1_1TimberInfo_1_1Cut.md) <br> |
| class | [**Hole**](classAIAC_1_1TimberInfo_1_1Hole.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**IsShowingAllComponents**](#variable-isshowingallcomponents)   = `false`<br> |
|  bool | [**IsShowingCotas**](#variable-isshowingcotas)   = `false`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; std::string &gt; | [**GetAllComponentsIDs**](#function-getallcomponentsids) () const<br> |
|  std::vector&lt; std::pair&lt; int, int &gt; &gt; | [**GetBboxEdgesIndices**](#function-getbboxedgesindices) () const<br> |
|  std::vector&lt; glm::vec3 &gt; | [**GetBoundingBox**](#function-getboundingbox) () const<br> |
|  [**Component**](classAIAC_1_1TimberInfo_1_1Component.md) \* | [**GetComponent**](#function-getcomponent) (const std::string & id) <br> |
|  [**Component**](classAIAC_1_1TimberInfo_1_1Component.md) \* | [**GetCurrentComponent**](#function-getcurrentcomponent) () <br> |
|  std::string | [**GetCurrentComponentID**](#function-getcurrentcomponentid) () <br> |
|  int | [**GetFabricatedComponents**](#function-getfabricatedcomponents) () <br>_Get the number of fabricate components._  |
|  float | [**GetFabricationProgress**](#function-getfabricationprogress) () <br>_Get the progress of fabrication in percentage._  |
|  std::string | [**GetID**](#function-getid) () const<br> |
|  int | [**GetTotalComponents**](#function-gettotalcomponents) () <br>_Get the total number of components._  |
|  void | [**HideAllComponentsExceptCurrent**](#function-hideallcomponentsexceptcurrent) () <br> |
|  void | [**SetCurrentComponentTo**](#function-setcurrentcomponentto) (std::string id) <br> |
|  void | [**SetNextComponentAsCurrent**](#function-setnextcomponentascurrent) () <br> |
|  void | [**SetPrevComponentAsCurrent**](#function-setprevcomponentascurrent) () <br> |
|  void | [**ShowAllComponents**](#function-showallcomponents) () <br> |
|  void | [**UpdateCotasVisibility**](#function-updatecotasvisibility) (bool visible) <br> |




























## Public Attributes Documentation




### variable IsShowingAllComponents 

```C++
bool AIAC::TimberInfo::IsShowingAllComponents;
```




<hr>



### variable IsShowingCotas 

```C++
bool AIAC::TimberInfo::IsShowingCotas;
```




<hr>
## Public Functions Documentation




### function GetAllComponentsIDs 

```C++
std::vector< std::string > AIAC::TimberInfo::GetAllComponentsIDs () const
```




<hr>



### function GetBboxEdgesIndices 

```C++
inline std::vector< std::pair< int, int > > AIAC::TimberInfo::GetBboxEdgesIndices () const
```




<hr>



### function GetBoundingBox 

```C++
inline std::vector< glm::vec3 > AIAC::TimberInfo::GetBoundingBox () const
```




<hr>



### function GetComponent 

```C++
inline Component * AIAC::TimberInfo::GetComponent (
    const std::string & id
) 
```




<hr>



### function GetCurrentComponent 

```C++
inline Component * AIAC::TimberInfo::GetCurrentComponent () 
```




<hr>



### function GetCurrentComponentID 

```C++
inline std::string AIAC::TimberInfo::GetCurrentComponentID () 
```




<hr>



### function GetFabricatedComponents 

_Get the number of fabricate components._ 
```C++
inline int AIAC::TimberInfo::GetFabricatedComponents () 
```



&lt; small utilities to calculate the progress of fabrication 


        

<hr>



### function GetFabricationProgress 

_Get the progress of fabrication in percentage._ 
```C++
inline float AIAC::TimberInfo::GetFabricationProgress () 
```




<hr>



### function GetID 

```C++
inline std::string AIAC::TimberInfo::GetID () const
```




<hr>



### function GetTotalComponents 

_Get the total number of components._ 
```C++
inline int AIAC::TimberInfo::GetTotalComponents () 
```




<hr>



### function HideAllComponentsExceptCurrent 

```C++
void AIAC::TimberInfo::HideAllComponentsExceptCurrent () 
```




<hr>



### function SetCurrentComponentTo 

```C++
void AIAC::TimberInfo::SetCurrentComponentTo (
    std::string id
) 
```




<hr>



### function SetNextComponentAsCurrent 

```C++
void AIAC::TimberInfo::SetNextComponentAsCurrent () 
```




<hr>



### function SetPrevComponentAsCurrent 

```C++
void AIAC::TimberInfo::SetPrevComponentAsCurrent () 
```




<hr>



### function ShowAllComponents 

```C++
void AIAC::TimberInfo::ShowAllComponents () 
```




<hr>



### function UpdateCotasVisibility 

```C++
void AIAC::TimberInfo::UpdateCotasVisibility (
    bool visible
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

