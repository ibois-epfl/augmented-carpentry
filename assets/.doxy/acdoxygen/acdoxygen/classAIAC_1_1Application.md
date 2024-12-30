

# Class AIAC::Application



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Application**](classAIAC_1_1Application.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Application**](#function-application) (const [**ApplicationSpecification**](structAIAC_1_1ApplicationSpecification.md) & appSpec) <br> |
|  void | [**Close**](#function-close) () <br> |
|  [**EventBus**](classAIAC_1_1EventBus.md) \*& | [**GetEventBus**](#function-geteventbus) () <br> |
|  [**GORegistry**](classAIAC_1_1GORegistry.md) \* | [**GetGORegistry**](#function-getgoregistry) () <br> |
|  std::shared\_ptr&lt; T &gt; | [**GetLayer**](#function-getlayer) () <br> |
|  [**Renderer**](classAIAC_1_1Renderer.md) \*& | [**GetRenderer**](#function-getrenderer) () <br> |
|  const [**ApplicationSpecification**](structAIAC_1_1ApplicationSpecification.md) & | [**GetSpecification**](#function-getspecification) () const<br> |
|  [**AIAC::Window**](classAIAC_1_1Window.md) \*& | [**GetWindow**](#function-getwindow) () <br> |
|  void | [**PushLayer**](#function-pushlayer) () <br> |
|  void | [**Run**](#function-run) () <br> |
| virtual  | [**~Application**](#function-application) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Application**](classAIAC_1_1Application.md) & | [**GetInstance**](#function-getinstance) () <br> |


























## Public Functions Documentation




### function Application 

```C++
AIAC::Application::Application (
    const ApplicationSpecification & appSpec
) 
```




<hr>



### function Close 

```C++
void AIAC::Application::Close () 
```




<hr>



### function GetEventBus 

```C++
inline EventBus *& AIAC::Application::GetEventBus () 
```




<hr>



### function GetGORegistry 

```C++
inline GORegistry * AIAC::Application::GetGORegistry () 
```




<hr>



### function GetLayer 

```C++
template<typename T>
inline std::shared_ptr< T > AIAC::Application::GetLayer () 
```




<hr>



### function GetRenderer 

```C++
inline Renderer *& AIAC::Application::GetRenderer () 
```




<hr>



### function GetSpecification 

```C++
inline const ApplicationSpecification & AIAC::Application::GetSpecification () const
```




<hr>



### function GetWindow 

```C++
inline AIAC::Window *& AIAC::Application::GetWindow () 
```




<hr>



### function PushLayer 

```C++
template<typename T>
inline void AIAC::Application::PushLayer () 
```




<hr>



### function Run 

```C++
void AIAC::Application::Run () 
```




<hr>



### function ~Application 

```C++
virtual AIAC::Application::~Application () 
```




<hr>
## Public Static Functions Documentation




### function GetInstance 

```C++
static inline Application & AIAC::Application::GetInstance () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/Application.h`

