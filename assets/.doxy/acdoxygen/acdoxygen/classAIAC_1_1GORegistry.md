

# Class AIAC::GORegistry



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**GORegistry**](classAIAC_1_1GORegistry.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  uint32\_t | [**CheckIfKeyExists**](#function-checkifkeyexists) (uint32\_t key) <br>_Check if a GO is in the registry by id._  |
|  void | [**Clear**](#function-clear) () <br>_Clear the registry from all the entries._  |
|  uint32\_t | [**Count**](#function-count) () const<br>_Get the total number of GOs in the registry._  |
|   | [**GORegistry**](#function-goregistry) () = default<br> |
|  void | [**GetAllGOs**](#function-getallgos-13) (std::vector&lt; std::shared\_ptr&lt; [**GOPoint**](classAIAC_1_1GOPoint.md) &gt; &gt; & points, std::vector&lt; std::shared\_ptr&lt; [**GOLine**](classAIAC_1_1GOLine.md) &gt; &gt; & lines, std::vector&lt; std::shared\_ptr&lt; [**GOCircle**](classAIAC_1_1GOCircle.md) &gt; &gt; & circles, std::vector&lt; std::shared\_ptr&lt; [**GOCylinder**](classAIAC_1_1GOCylinder.md) &gt; &gt; & cylinders, std::vector&lt; std::shared\_ptr&lt; [**GOPolyline**](classAIAC_1_1GOPolyline.md) &gt; &gt; & polylines, std::vector&lt; std::shared\_ptr&lt; [**GOTriangle**](classAIAC_1_1GOTriangle.md) &gt; &gt; & triangles, std::vector&lt; std::shared\_ptr&lt; [**GOMesh**](classAIAC_1_1GOMesh.md) &gt; &gt; & meshes, std::vector&lt; std::shared\_ptr&lt; [**GOText**](classAIAC_1_1GOText.md) &gt; &gt; & texts) <br>_Get the All GOs by category._  |
|  std::vector&lt; std::shared\_ptr&lt; T &gt; &gt; | [**GetAllGOs**](#function-getallgos-23) () <br>_Get all GOs of a specific type in the registry._  |
|  void | [**GetAllGOs**](#function-getallgos-33) (std::vector&lt; std::shared\_ptr&lt; [**GOPrimitive**](classAIAC_1_1GOPrimitive.md) &gt; &gt; & goVector) <br>_Get the All GOs as primitives._  |
|  std::shared\_ptr&lt; T &gt; | [**GetGO**](#function-getgo) (const uint32\_t & id) <br>_Retrieve the GO pointer from the registry by index and template as GOObject._  |
|  void | [**Init**](#function-init) () <br> |
|  void | [**Register**](#function-register-12) (std::shared\_ptr&lt; T &gt; go) <br>_Add a GO to the registry._  |
|  void | [**Register**](#function-register-22) (const uint32\_t & id, std::shared\_ptr&lt; T &gt; go) <br>_Add a GO to the registry with a given id._  |
|  void | [**Unregister**](#function-unregister) (const uint32\_t & id) <br>_Erase the GO from the register._  |
|   | [**~GORegistry**](#function-goregistry) () = default<br> |




























## Public Functions Documentation




### function CheckIfKeyExists 

_Check if a GO is in the registry by id._ 
```C++
inline uint32_t AIAC::GORegistry::CheckIfKeyExists (
    uint32_t key
) 
```





**Parameters:**


* `id` Id of the object to check. 




        

<hr>



### function Clear 

_Clear the registry from all the entries._ 
```C++
inline void AIAC::GORegistry::Clear () 
```




<hr>



### function Count 

_Get the total number of GOs in the registry._ 
```C++
inline uint32_t AIAC::GORegistry::Count () const
```




<hr>



### function GORegistry 

```C++
AIAC::GORegistry::GORegistry () = default
```




<hr>



### function GetAllGOs [1/3]

_Get the All GOs by category._ 
```C++
inline void AIAC::GORegistry::GetAllGOs (
    std::vector< std::shared_ptr< GOPoint > > & points,
    std::vector< std::shared_ptr< GOLine > > & lines,
    std::vector< std::shared_ptr< GOCircle > > & circles,
    std::vector< std::shared_ptr< GOCylinder > > & cylinders,
    std::vector< std::shared_ptr< GOPolyline > > & polylines,
    std::vector< std::shared_ptr< GOTriangle > > & triangles,
    std::vector< std::shared_ptr< GOMesh > > & meshes,
    std::vector< std::shared_ptr< GOText > > & texts
) 
```





**Parameters:**


* `points` A vector of all GOPoints to pass as reference. 
* `lines` A vector of all GOLines to pass as reference. 
* `circles` A vector of all GOCircles to pass as reference. 
* `cylinders` A vector of all GOCylinders to pass as reference. 
* `polylines` A vector of all GOPolylines to pass as reference. 
* `triangles` A vector of all GOTriangles to pass as reference. 
* `texts` A vector of all GOTexts to pass as reference. 




        

<hr>



### function GetAllGOs [2/3]

_Get all GOs of a specific type in the registry._ 
```C++
template<typename T>
inline std::vector< std::shared_ptr< T > > AIAC::GORegistry::GetAllGOs () 
```




<hr>



### function GetAllGOs [3/3]

_Get the All GOs as primitives._ 
```C++
inline void AIAC::GORegistry::GetAllGOs (
    std::vector< std::shared_ptr< GOPrimitive > > & goVector
) 
```





**Parameters:**


* `goVector` A reference vector to load with all the GOPrimitives. 




        

<hr>



### function GetGO 

_Retrieve the GO pointer from the registry by index and template as GOObject._ 
```C++
template<typename T>
inline std::shared_ptr< T > AIAC::GORegistry::GetGO (
    const uint32_t & id
) 
```





**Parameters:**


* `id` Id of the object when created. 




        

<hr>



### function Init 

```C++
inline void AIAC::GORegistry::Init () 
```




<hr>



### function Register [1/2]

_Add a GO to the registry._ 
```C++
template<typename T>
inline void AIAC::GORegistry::Register (
    std::shared_ptr< T > go
) 
```





**Parameters:**


* `id` Id of the object to register. 
* `go` Smart pointer to the object to register. 




        

<hr>



### function Register [2/2]

_Add a GO to the registry with a given id._ 
```C++
template<typename T>
inline void AIAC::GORegistry::Register (
    const uint32_t & id,
    std::shared_ptr< T > go
) 
```





**Parameters:**


* `id` Id of the object to register. 
* `go` Smart pointer to the object to register. 




        

<hr>



### function Unregister 

_Erase the GO from the register._ 
```C++
inline void AIAC::GORegistry::Unregister (
    const uint32_t & id
) 
```





**Parameters:**


* `id` Id of the object to erase from the register. 




        

<hr>



### function ~GORegistry 

```C++
AIAC::GORegistry::~GORegistry () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/GOSys/GORegistry.h`

