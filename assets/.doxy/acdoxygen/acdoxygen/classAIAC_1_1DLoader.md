

# Class AIAC::DLoader



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**DLoader**](classAIAC_1_1DLoader.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CvtAssimpMeshColorsToGlmVector**](#function-cvtassimpmeshcolorstoglmvector) (const aiMesh \* mesh, std::vector&lt; glm::vec3 &gt; & glmColors) <br> |
|  void | [**CvtAssimpMeshFacesToGlmVector**](#function-cvtassimpmeshfacestoglmvector) (const aiMesh \* mesh, std::vector&lt; uint32\_t &gt; & glmIndices) <br> |
|  void | [**CvtAssimpMeshNormalsToGlmVector**](#function-cvtassimpmeshnormalstoglmvector) (const aiMesh \* mesh, std::vector&lt; glm::vec3 &gt; & glmNormals) <br> |
|  bool | [**CvtAssimpMeshToGOMesh**](#function-cvtassimpmeshtogomesh) (const aiMesh \* mesh, [**GOMesh**](classAIAC_1_1GOMesh.md) & goMesh) <br> |
|  void | [**CvtAssimpMeshVerticesToGlmVector**](#function-cvtassimpmeshverticestoglmvector) (const aiMesh \* mesh, std::vector&lt; glm::vec3 &gt; & glmVertices) <br> |
|   | [**DLoader**](#function-dloader) () = default<br> |
|  bool | [**LoadGOMesh**](#function-loadgomesh) (const char \* path, [**GOMesh**](classAIAC_1_1GOMesh.md) & goMesh) <br> |
|   | [**~DLoader**](#function-dloader) () = default<br> |




























## Public Functions Documentation




### function CvtAssimpMeshColorsToGlmVector 

```C++
void AIAC::DLoader::CvtAssimpMeshColorsToGlmVector (
    const aiMesh * mesh,
    std::vector< glm::vec3 > & glmColors
) 
```




<hr>



### function CvtAssimpMeshFacesToGlmVector 

```C++
void AIAC::DLoader::CvtAssimpMeshFacesToGlmVector (
    const aiMesh * mesh,
    std::vector< uint32_t > & glmIndices
) 
```




<hr>



### function CvtAssimpMeshNormalsToGlmVector 

```C++
void AIAC::DLoader::CvtAssimpMeshNormalsToGlmVector (
    const aiMesh * mesh,
    std::vector< glm::vec3 > & glmNormals
) 
```




<hr>



### function CvtAssimpMeshToGOMesh 

```C++
bool AIAC::DLoader::CvtAssimpMeshToGOMesh (
    const aiMesh * mesh,
    GOMesh & goMesh
) 
```




<hr>



### function CvtAssimpMeshVerticesToGlmVector 

```C++
void AIAC::DLoader::CvtAssimpMeshVerticesToGlmVector (
    const aiMesh * mesh,
    std::vector< glm::vec3 > & glmVertices
) 
```




<hr>



### function DLoader 

```C++
AIAC::DLoader::DLoader () = default
```




<hr>



### function LoadGOMesh 

```C++
bool AIAC::DLoader::LoadGOMesh (
    const char * path,
    GOMesh & goMesh
) 
```




<hr>



### function ~DLoader 

```C++
AIAC::DLoader::~DLoader () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/DLoader.h`

