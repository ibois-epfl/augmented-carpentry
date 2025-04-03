

# Class AIAC::ACInfoModel



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ACInfoModel**](classAIAC_1_1ACInfoModel.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ACInfoModel**](#function-acinfomodel) () <br> |
|  void | [**AddMeasuredBboxLength**](#function-addmeasuredbboxlength) (const float diff) <br> |
|  void | [**AdjustScale**](#function-adjustscale) () <br>_Utils._  |
|  void | [**Clear**](#function-clear) () <br>_Clear the loaded data._  |
|  pugi::xml\_document & | [**GetDoc**](#function-getdoc) () <br>_Get the pugi::xml\_document object._  |
|  const std::string & | [**GetFilePath**](#function-getfilepath) () const<br>_Get the filepath to the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._ |
|  float | [**GetLength**](#function-getlength) () <br>_Get the length of the acim, which is calculated by averaging the four long edges of the bounding box._  |
|  float | [**GetMeasuredBboxLength**](#function-getmeasuredbboxlength) () const<br> |
|  const std::string | [**GetName**](#function-getname) () const<br>_Get the name of the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _without the extension._ |
|  float | [**GetRealWorldLength**](#function-getrealworldlength) () <br>_Get the length of the acim, which is calculated by averaging the four long edges of the bounding box._  |
|  [**TimberInfo**](classAIAC_1_1TimberInfo.md) & | [**GetTimberInfo**](#function-gettimberinfo) () <br>_Get the_ [_**TimberInfo**_](classAIAC_1_1TimberInfo.md) _object._ |
|  bool | [**Load**](#function-load) (std::string path) <br>_Load a .acim model from a file._  |
|  void | [**Save**](#function-save) () <br>_Save the current state to the loaded .acim file._  |
|  void | [**SetBboxVisibility**](#function-setbboxvisibility) (bool visible) <br> |
|  void | [**Transform**](#function-transform) (glm::mat4x4 transformMat) <br>_transform all the_ [_**GOPrimitive**_](classAIAC_1_1GOPrimitive.md) _belonging to the_[_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) __ |
|  void | [**UpdateBboxGOLine**](#function-updatebboxgoline) () <br>_Update the bounding box of the timber (use the current Active_ [_**TimberInfo**_](classAIAC_1_1TimberInfo.md) _)_ |
|   | [**~ACInfoModel**](#function-acinfomodel) () <br> |




























## Public Functions Documentation




### function ACInfoModel 

```C++
inline AIAC::ACInfoModel::ACInfoModel () 
```




<hr>



### function AddMeasuredBboxLength 

```C++
void AIAC::ACInfoModel::AddMeasuredBboxLength (
    const float diff
) 
```



Increase / decrease real world length based on the measurement 


        

<hr>



### function AdjustScale 

_Utils._ 
```C++
void AIAC::ACInfoModel::AdjustScale () 
```



Adjust the scale of the model based on the measured result 


        

<hr>



### function Clear 

_Clear the loaded data._ 
```C++
void AIAC::ACInfoModel::Clear () 
```




<hr>



### function GetDoc 

_Get the pugi::xml\_document object._ 
```C++
inline pugi::xml_document & AIAC::ACInfoModel::GetDoc () 
```




<hr>



### function GetFilePath 

_Get the filepath to the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _._
```C++
inline const std::string & AIAC::ACInfoModel::GetFilePath () const
```




<hr>



### function GetLength 

_Get the length of the acim, which is calculated by averaging the four long edges of the bounding box._ 
```C++
float AIAC::ACInfoModel::GetLength () 
```





**Returns:**

The length of the acim bounding box. (in TSLAM unit) 





        

<hr>



### function GetMeasuredBboxLength 

```C++
inline float AIAC::ACInfoModel::GetMeasuredBboxLength () const
```



Get the real world length of the bounding box (in Real World unit, meter) 


        

<hr>



### function GetName 

_Get the name of the loaded_ [_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) _without the extension._
```C++
inline const std::string AIAC::ACInfoModel::GetName () const
```




<hr>



### function GetRealWorldLength 

_Get the length of the acim, which is calculated by averaging the four long edges of the bounding box._ 
```C++
inline float AIAC::ACInfoModel::GetRealWorldLength () 
```





**Returns:**

The length of the acim bounding box. (in Real World unit, meter) 





        

<hr>



### function GetTimberInfo 

_Get the_ [_**TimberInfo**_](classAIAC_1_1TimberInfo.md) _object._
```C++
inline TimberInfo & AIAC::ACInfoModel::GetTimberInfo () 
```




<hr>



### function Load 

_Load a .acim model from a file._ 
```C++
bool AIAC::ACInfoModel::Load (
    std::string path
) 
```





**Parameters:**


* `path` Path to the model file. 



**Returns:**

true if the file is loaded successfully, false otherwise. 





        

<hr>



### function Save 

_Save the current state to the loaded .acim file._ 
```C++
void AIAC::ACInfoModel::Save () 
```




<hr>



### function SetBboxVisibility 

```C++
void AIAC::ACInfoModel::SetBboxVisibility (
    bool visible
) 
```



Set the visibility of bbox to true or false 


        

<hr>



### function Transform 

_transform all the_ [_**GOPrimitive**_](classAIAC_1_1GOPrimitive.md) _belonging to the_[_**ACInfoModel**_](classAIAC_1_1ACInfoModel.md) __
```C++
void AIAC::ACInfoModel::Transform (
    glm::mat4x4 transformMat
) 
```





**Parameters:**


* `transformMat` transformation matrix 




        

<hr>



### function UpdateBboxGOLine 

_Update the bounding box of the timber (use the current Active_ [_**TimberInfo**_](classAIAC_1_1TimberInfo.md) _)_
```C++
void AIAC::ACInfoModel::UpdateBboxGOLine () 
```




<hr>



### function ~ACInfoModel 

```C++
inline AIAC::ACInfoModel::~ACInfoModel () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoModel.h`

