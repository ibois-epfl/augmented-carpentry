

# Class AIAC::ACInfoToolheadManager



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**ACInfoToolheadManager**](classAIAC_1_1ACInfoToolheadManager.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ACInfoToolheadManager**](#function-acinfotoolheadmanager) () <br> |
|  std::shared\_ptr&lt; [**ACInfoToolhead**](classAIAC_1_1ACInfoToolhead.md) &gt; | [**GetActiveToolhead**](#function-getactivetoolhead) () const<br>_Get the active toolhead model._  |
|  std::string | [**GetActiveToolheadName**](#function-getactivetoolheadname) () const<br>_Get the active toolhead model's name._  |
|  ACToolHeadType | [**GetActiveToolheadType**](#function-getactivetoolheadtype) () const<br>_Get the current active toolhead's type._  |
|  std::shared\_ptr&lt; [**ACInfoToolhead**](classAIAC_1_1ACInfoToolhead.md) &gt; | [**GetToolhead**](#function-gettoolhead) (const std::string & toolheadName) const<br>_Get the toolhead model by its name._  |
|  std::vector&lt; std::string &gt; | [**GetToolheadNames**](#function-gettoolheadnames) () const<br>_Return the list of names of the toolheads loaded._  |
|  ACToolHeadType | [**GetToolheadType**](#function-gettoolheadtype) (const std::string & toolheadName) const<br>_Get the toolhead's type by its name._  |
|  void | [**LoadToolheadModels**](#function-loadtoolheadmodels) () <br>_Load each toolhead model acit/obj from the dataset dir._  |
|  void | [**SetActiveToolhead**](#function-setactivetoolhead) (const std::string & toolheadName) <br>_Set a toolhead model as active by its name._  |




























## Public Functions Documentation




### function ACInfoToolheadManager 

```C++
inline AIAC::ACInfoToolheadManager::ACInfoToolheadManager () 
```




<hr>



### function GetActiveToolhead 

_Get the active toolhead model._ 
```C++
inline std::shared_ptr< ACInfoToolhead > AIAC::ACInfoToolheadManager::GetActiveToolhead () const
```




<hr>



### function GetActiveToolheadName 

_Get the active toolhead model's name._ 
```C++
inline std::string AIAC::ACInfoToolheadManager::GetActiveToolheadName () const
```




<hr>



### function GetActiveToolheadType 

_Get the current active toolhead's type._ 
```C++
inline ACToolHeadType AIAC::ACInfoToolheadManager::GetActiveToolheadType () const
```




<hr>



### function GetToolhead 

_Get the toolhead model by its name._ 
```C++
inline std::shared_ptr< ACInfoToolhead > AIAC::ACInfoToolheadManager::GetToolhead (
    const std::string & toolheadName
) const
```




<hr>



### function GetToolheadNames 

_Return the list of names of the toolheads loaded._ 
```C++
inline std::vector< std::string > AIAC::ACInfoToolheadManager::GetToolheadNames () const
```




<hr>



### function GetToolheadType 

_Get the toolhead's type by its name._ 
```C++
inline ACToolHeadType AIAC::ACInfoToolheadManager::GetToolheadType (
    const std::string & toolheadName
) const
```




<hr>



### function LoadToolheadModels 

_Load each toolhead model acit/obj from the dataset dir._ 
```C++
void AIAC::ACInfoToolheadManager::LoadToolheadModels () 
```




<hr>



### function SetActiveToolhead 

_Set a toolhead model as active by its name._ 
```C++
void AIAC::ACInfoToolheadManager::SetActiveToolhead (
    const std::string & toolheadName
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/ACInfoToolheadManager.h`

