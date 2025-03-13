

# Class AIAC::PaneUI



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**PaneUI**](classAIAC_1_1PaneUI.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**CollapseState**](#enum-collapsestate)  <br> |
| typedef std::function&lt; void()&gt; | [**Func**](#typedef-func)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CheckOnCollapsing**](#function-checkoncollapsing) (Args &&... args) <br> |
|   | [**PaneUI**](#function-paneui) (const char \* label, bool isCollapsed, Func func, Func onCollapseCallback=[]{}) <br> |
|  void | [**Show**](#function-show) (Args &&... args) <br> |




























## Public Types Documentation




### enum CollapseState 

```C++
enum AIAC::PaneUI::CollapseState {
    OPEN,
    ON_COLLAPSING,
    COLLAPSE
};
```




<hr>



### typedef Func 

```C++
typedef std::function<void()> AIAC::PaneUI::Func;
```




<hr>
## Public Functions Documentation




### function CheckOnCollapsing 

```C++
template<typename... Args>
void AIAC::PaneUI::CheckOnCollapsing (
    Args &&... args
) 
```




<hr>



### function PaneUI 

```C++
inline AIAC::PaneUI::PaneUI (
    const char * label,
    bool isCollapsed,
    Func func,
    Func onCollapseCallback=[]{}
) 
```




<hr>



### function Show 

```C++
template<typename... Args>
void AIAC::PaneUI::Show (
    Args &&... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/LayerUI.h`

