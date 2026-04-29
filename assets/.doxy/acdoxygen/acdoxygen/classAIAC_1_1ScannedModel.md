

# Class AIAC::ScannedModel



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ScannedModel**](classAIAC_1_1ScannedModel.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**BuildBoundingBox**](#function-buildboundingbox) () <br>_Build the bounding box based on the ply model._  |
|  std::vector&lt; std::pair&lt; int, int &gt; &gt; | [**GetBboxEdgesIndices**](#function-getbboxedgesindices) () const<br> |
|  std::vector&lt; glm::vec3 &gt; | [**GetBoundingBox**](#function-getboundingbox) () const<br>_Get the bounding box of the ply model._  |
|  float | [**GetLength**](#function-getlength) () <br>_Get the length of the scanned model, which is calculated by averaging the four edges of the bounding box._  |
|  bool | [**Load**](#function-load) (std::string path) <br>_Load a .ply model from a file._  |
|   | [**ScannedModel**](#function-scannedmodel) () <br> |
|  void | [**UpdateBboxGOLine**](#function-updatebboxgoline) () <br>_Update Boundary Box_ [_**GOLine**_](classAIAC_1_1GOLine.md) _._ |
|   | [**~ScannedModel**](#function-scannedmodel) () <br> |




























## Public Functions Documentation




### function BuildBoundingBox 

_Build the bounding box based on the ply model._ 
```C++
void AIAC::ScannedModel::BuildBoundingBox () 
```




<hr>



### function GetBboxEdgesIndices 

```C++
inline std::vector< std::pair< int, int > > AIAC::ScannedModel::GetBboxEdgesIndices () const
```




<hr>



### function GetBoundingBox 

_Get the bounding box of the ply model._ 
```C++
inline std::vector< glm::vec3 > AIAC::ScannedModel::GetBoundingBox () const
```





**Returns:**

The bounding box of the ply model. 





        

<hr>



### function GetLength 

_Get the length of the scanned model, which is calculated by averaging the four edges of the bounding box._ 
```C++
float AIAC::ScannedModel::GetLength () 
```





**Returns:**

The length of the scanned model. (in TSLAM unit) 





        

<hr>



### function Load 

_Load a .ply model from a file._ 
```C++
bool AIAC::ScannedModel::Load (
    std::string path
) 
```





**Parameters:**


* `path` Path to the model file. 



**Returns:**

True if the model is loaded successfully, false otherwise. 





        

<hr>



### function ScannedModel 

```C++
inline AIAC::ScannedModel::ScannedModel () 
```




<hr>



### function UpdateBboxGOLine 

_Update Boundary Box_ [_**GOLine**_](classAIAC_1_1GOLine.md) _._
```C++
void AIAC::ScannedModel::UpdateBboxGOLine () 
```




<hr>



### function ~ScannedModel 

```C++
inline AIAC::ScannedModel::~ScannedModel () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ScannedModel.h`

