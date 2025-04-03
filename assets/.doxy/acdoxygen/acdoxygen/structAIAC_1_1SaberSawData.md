

# Struct AIAC::SaberSawData



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**SaberSawData**](structAIAC_1_1SaberSawData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::string | [**NameACIT**](#variable-nameacit)  <br>_name of the toolhead_  |
|  glm::vec3 | [**NormEndACIT**](#variable-normendacit)  <br>_end of the normal of the blade plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormEndGO**](#variable-normendgo)  <br> |
|  glm::vec3 | [**NormStartACIT**](#variable-normstartacit)  <br>_start of the normal of the blade plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormStartGO**](#variable-normstartgo)  <br> |
|  glm::vec3 | [**ToolbaseACIT**](#variable-toolbaseacit)  <br>_position of the base of the toolhead_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**ToolbaseGO**](#variable-toolbasego)  <br>_GOPoints equivalent._  |
|  glm::vec3 | [**TooltipACIT**](#variable-tooltipacit)  <br>_position of the tip of the toolhead_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**TooltipGO**](#variable-tooltipgo)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SaberSawData**](#function-sabersawdata) () <br> |




























## Public Attributes Documentation




### variable NameACIT 

_name of the toolhead_ 
```C++
std::string AIAC::SaberSawData::NameACIT;
```




<hr>



### variable NormEndACIT 

_end of the normal of the blade plane_ 
```C++
glm::vec3 AIAC::SaberSawData::NormEndACIT;
```




<hr>



### variable NormEndGO 

```C++
std::shared_ptr<GOPoint> AIAC::SaberSawData::NormEndGO;
```




<hr>



### variable NormStartACIT 

_start of the normal of the blade plane_ 
```C++
glm::vec3 AIAC::SaberSawData::NormStartACIT;
```




<hr>



### variable NormStartGO 

```C++
std::shared_ptr<GOPoint> AIAC::SaberSawData::NormStartGO;
```




<hr>



### variable ToolbaseACIT 

_position of the base of the toolhead_ 
```C++
glm::vec3 AIAC::SaberSawData::ToolbaseACIT;
```




<hr>



### variable ToolbaseGO 

_GOPoints equivalent._ 
```C++
std::shared_ptr<GOPoint> AIAC::SaberSawData::ToolbaseGO;
```




<hr>



### variable TooltipACIT 

_position of the tip of the toolhead_ 
```C++
glm::vec3 AIAC::SaberSawData::TooltipACIT;
```




<hr>



### variable TooltipGO 

```C++
std::shared_ptr<GOPoint> AIAC::SaberSawData::TooltipGO;
```




<hr>
## Public Functions Documentation




### function SaberSawData 

```C++
inline AIAC::SaberSawData::SaberSawData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoToolhead.h`

