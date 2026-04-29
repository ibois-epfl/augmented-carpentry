

# Class AIAC::EventBus



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**EventBus**](classAIAC_1_1EventBus.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DispatchEvent**](#function-dispatchevent) (const EventPointer & sharedPtrEvent) <br> |
|  void | [**EnqueueEvent**](#function-enqueueevent) (const EventPointer & sharedPtrEvent) <br> |
|  void | [**Init**](#function-init) () <br> |
|  bool | [**IsEventQueueEmpty**](#function-iseventqueueempty) () const<br> |
|  void | [**ProcessQueue**](#function-processqueue) () <br> |
|   | [**~EventBus**](#function-eventbus) () = default<br> |




























## Public Functions Documentation




### function DispatchEvent 

```C++
inline void AIAC::EventBus::DispatchEvent (
    const EventPointer & sharedPtrEvent
) 
```




<hr>



### function EnqueueEvent 

```C++
inline void AIAC::EventBus::EnqueueEvent (
    const EventPointer & sharedPtrEvent
) 
```




<hr>



### function Init 

```C++
inline void AIAC::EventBus::Init () 
```




<hr>



### function IsEventQueueEmpty 

```C++
inline bool AIAC::EventBus::IsEventQueueEmpty () const
```




<hr>



### function ProcessQueue 

```C++
inline void AIAC::EventBus::ProcessQueue () 
```




<hr>



### function ~EventBus 

```C++
AIAC::EventBus::~EventBus () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/EventBus.h`

