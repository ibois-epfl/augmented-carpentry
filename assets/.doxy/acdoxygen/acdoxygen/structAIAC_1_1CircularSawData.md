

# Struct AIAC::CircularSawData



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CircularSawData**](structAIAC_1_1CircularSawData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**CenterACIT**](#variable-centeracit)  <br>_center of the circle defining the circular blade_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**CenterGO**](#variable-centergo)  <br>_GOPoints equivalent._  |
|  std::string | [**NameACIT**](#variable-nameacit)  <br>_name of the toolhead_  |
|  glm::vec3 | [**NormEndACIT**](#variable-normendacit)  <br>_end of the normal of the blade plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormEndGO**](#variable-normendgo)  <br> |
|  glm::vec3 | [**NormStartACIT**](#variable-normstartacit)  <br>_start of the normal of the blade plane_  |
|  std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; | [**NormStartGO**](#variable-normstartgo)  <br> |
|  float | [**OverhangACIT**](#variable-overhangacit)  <br>_the overhang width of the teeth of the blade from one side_  |
|  float | [**RadiusACIT**](#variable-radiusacit)  <br>_radius of the circular blade_  |
|  float | [**ThicknessACIT**](#variable-thicknessacit)  <br>_the overhaul thickness of the blade_  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CircularSawData**](#function-circularsawdata) () <br> |




























## Public Attributes Documentation




### variable CenterACIT 

_center of the circle defining the circular blade_ 
```C++
glm::vec3 AIAC::CircularSawData::CenterACIT;
```




<hr>



### variable CenterGO 

_GOPoints equivalent._ 
```C++
std::shared_ptr<GOPoint> AIAC::CircularSawData::CenterGO;
```




<hr>



### variable NameACIT 

_name of the toolhead_ 
```C++
std::string AIAC::CircularSawData::NameACIT;
```




<hr>



### variable NormEndACIT 

_end of the normal of the blade plane_ 
```C++
glm::vec3 AIAC::CircularSawData::NormEndACIT;
```




<hr>



### variable NormEndGO 

```C++
std::shared_ptr<GOPoint> AIAC::CircularSawData::NormEndGO;
```




<hr>



### variable NormStartACIT 

_start of the normal of the blade plane_ 
```C++
glm::vec3 AIAC::CircularSawData::NormStartACIT;
```




<hr>



### variable NormStartGO 

```C++
std::shared_ptr<GOPoint> AIAC::CircularSawData::NormStartGO;
```




<hr>



### variable OverhangACIT 

_the overhang width of the teeth of the blade from one side_ 
```C++
float AIAC::CircularSawData::OverhangACIT;
```




<hr>



### variable RadiusACIT 

_radius of the circular blade_ 
```C++
float AIAC::CircularSawData::RadiusACIT;
```




<hr>



### variable ThicknessACIT 

_the overhaul thickness of the blade_ 
```C++
float AIAC::CircularSawData::ThicknessACIT;
```




<hr>
## Public Functions Documentation




### function CircularSawData 

```C++
inline AIAC::CircularSawData::CircularSawData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoToolhead.h`

