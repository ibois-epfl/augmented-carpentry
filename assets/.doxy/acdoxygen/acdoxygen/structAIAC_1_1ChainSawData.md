

# Struct AIAC::ChainSawData



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ChainSawData**](structAIAC_1_1ChainSawData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**ChainBaseACIT**](#variable-chainbaseacit)  <br>_point start of the basetool_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**ChainBaseGO**](#variable-chainbasego)  <br>_GOPoints equivalent._  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**ChainEndGO**](#variable-chainendgo)  <br> |
|  glm::vec3 | [**ChainMidACIT**](#variable-chainmidacit)  <br>_point in the middle of the chain_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**ChainMidGO**](#variable-chainmidgo)  <br> |
|  glm::vec3 | [**ChainNormEndACIT**](#variable-chainnormendacit)  <br>_point end of the chain before the round tip_  |
|  std::string | [**NameACIT**](#variable-nameacit)  <br>_name of the toolhead_  |
|  glm::vec3 | [**NormEndACIT**](#variable-normendacit)  <br>_end of the normal of the plateau plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormEndGO**](#variable-normendgo)  <br> |
|  glm::vec3 | [**NormStartACIT**](#variable-normstartacit)  <br>_start of the normal of the plateau plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormStartGO**](#variable-normstartgo)  <br> |
|  float | [**OverhangACIT**](#variable-overhangacit)  <br>_the overhang width of the teeth of the blade from one side_  |
|  float | [**ThicknessACIT**](#variable-thicknessacit)  <br>_the overhaul thickness of the blade_  |
|  float | [**WidthACIT**](#variable-widthacit)  <br>_width of the chain_  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ChainSawData**](#function-chainsawdata) () <br> |




























## Public Attributes Documentation




### variable ChainBaseACIT 

_point start of the basetool_ 
```C++
glm::vec3 AIAC::ChainSawData::ChainBaseACIT;
```




<hr>



### variable ChainBaseGO 

_GOPoints equivalent._ 
```C++
std::shared_ptr<GOPoint> AIAC::ChainSawData::ChainBaseGO;
```




<hr>



### variable ChainEndGO 

```C++
std::shared_ptr<GOPoint> AIAC::ChainSawData::ChainEndGO;
```




<hr>



### variable ChainMidACIT 

_point in the middle of the chain_ 
```C++
glm::vec3 AIAC::ChainSawData::ChainMidACIT;
```




<hr>



### variable ChainMidGO 

```C++
std::shared_ptr<GOPoint> AIAC::ChainSawData::ChainMidGO;
```




<hr>



### variable ChainNormEndACIT 

_point end of the chain before the round tip_ 
```C++
glm::vec3 AIAC::ChainSawData::ChainNormEndACIT;
```




<hr>



### variable NameACIT 

_name of the toolhead_ 
```C++
std::string AIAC::ChainSawData::NameACIT;
```




<hr>



### variable NormEndACIT 

_end of the normal of the plateau plane_ 
```C++
glm::vec3 AIAC::ChainSawData::NormEndACIT;
```




<hr>



### variable NormEndGO 

```C++
std::shared_ptr<GOPoint> AIAC::ChainSawData::NormEndGO;
```




<hr>



### variable NormStartACIT 

_start of the normal of the plateau plane_ 
```C++
glm::vec3 AIAC::ChainSawData::NormStartACIT;
```




<hr>



### variable NormStartGO 

```C++
std::shared_ptr<GOPoint> AIAC::ChainSawData::NormStartGO;
```




<hr>



### variable OverhangACIT 

_the overhang width of the teeth of the blade from one side_ 
```C++
float AIAC::ChainSawData::OverhangACIT;
```




<hr>



### variable ThicknessACIT 

_the overhaul thickness of the blade_ 
```C++
float AIAC::ChainSawData::ThicknessACIT;
```




<hr>



### variable WidthACIT 

_width of the chain_ 
```C++
float AIAC::ChainSawData::WidthACIT;
```




<hr>
## Public Functions Documentation




### function ChainSawData 

```C++
inline AIAC::ChainSawData::ChainSawData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoToolhead.h`

