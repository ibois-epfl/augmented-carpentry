

# Class AIAC::CutCircularSawFeedback



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CutCircularSawFeedback**](classAIAC_1_1CutCircularSawFeedback.md)








Inherits the following classes: [AIAC::FabFeedback](classAIAC_1_1FabFeedback.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**IsRefFacesSelectedManually**](#variable-isreffacesselectedmanually)   = `false`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](#function-activate) () override<br> |
|   | [**CutCircularSawFeedback**](#function-cutcircularsawfeedback) () = default<br> |
| virtual void | [**Deactivate**](#function-deactivate) () override<br> |
|  void | [**EnableCutPlane**](#function-enablecutplane) (bool enable) <br> |
|  void | [**ManuallyScrollRefFace**](#function-manuallyscrollrefface) (int scrollDirection) <br> |
| virtual void | [**Update**](#function-update) () override<br> |
|   | [**~CutCircularSawFeedback**](#function-cutcircularsawfeedback) () = default<br> |


## Public Functions inherited from AIAC::FabFeedback

See [AIAC::FabFeedback](classAIAC_1_1FabFeedback.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Activate**](classAIAC_1_1FabFeedback.md#function-activate) () <br> |
| virtual void | [**Deactivate**](classAIAC_1_1FabFeedback.md#function-deactivate) () <br> |
|   | [**FabFeedback**](classAIAC_1_1FabFeedback.md#function-fabfeedback) () <br> |
| virtual void | [**Update**](classAIAC_1_1FabFeedback.md#function-update) () <br> |
|   | [**~FabFeedback**](classAIAC_1_1FabFeedback.md#function-fabfeedback) () = default<br> |
















## Protected Attributes inherited from AIAC::FabFeedback

See [AIAC::FabFeedback](classAIAC_1_1FabFeedback.md)

| Type | Name |
| ---: | :--- |
|  float | [**m\_ScaleFactor**](classAIAC_1_1FabFeedback.md#variable-m_scalefactor)   = `0.0f`<br> |






































## Public Attributes Documentation




### variable IsRefFacesSelectedManually 

```C++
bool AIAC::CutCircularSawFeedback::IsRefFacesSelectedManually;
```




<hr>
## Public Functions Documentation




### function Activate 

```C++
virtual void AIAC::CutCircularSawFeedback::Activate () override
```



Implements [*AIAC::FabFeedback::Activate*](classAIAC_1_1FabFeedback.md#function-activate)


<hr>



### function CutCircularSawFeedback 

```C++
AIAC::CutCircularSawFeedback::CutCircularSawFeedback () = default
```




<hr>



### function Deactivate 

```C++
virtual void AIAC::CutCircularSawFeedback::Deactivate () override
```



Implements [*AIAC::FabFeedback::Deactivate*](classAIAC_1_1FabFeedback.md#function-deactivate)


<hr>



### function EnableCutPlane 

```C++
inline void AIAC::CutCircularSawFeedback::EnableCutPlane (
    bool enable
) 
```




<hr>



### function ManuallyScrollRefFace 

```C++
void AIAC::CutCircularSawFeedback::ManuallyScrollRefFace (
    int scrollDirection
) 
```



Manually select the reference face (the nearest parallel face) 

**Parameters:**


* `scrollDirection` when &gt; 0, goes to next; &lt;= 0, goes back. 




        

<hr>



### function Update 

```C++
virtual void AIAC::CutCircularSawFeedback::Update () override
```



Implements [*AIAC::FabFeedback::Update*](classAIAC_1_1FabFeedback.md#function-update)


<hr>



### function ~CutCircularSawFeedback 

```C++
AIAC::CutCircularSawFeedback::~CutCircularSawFeedback () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Feedback/CutCircularSawFeedback.h`

