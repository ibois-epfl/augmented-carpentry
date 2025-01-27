

# Struct AIAC::EventPolicy



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**EventPolicy**](structAIAC_1_1EventPolicy.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::priority\_queue&lt; Item, std::vector&lt; Item &gt;, [**EventCompare**](structAIAC_1_1EventCompare.md) &gt; | [**PrioriQueueListtyQueue**](#typedef-prioriqueuelisttyqueue)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  EventCategory | [**GetCategory**](#function-getcategory) (const EventPointer & event) <br> |
|  EventType | [**GetEvent**](#function-getevent) (const EventPointer & event) <br> |


























## Public Types Documentation




### typedef PrioriQueueListtyQueue 

```C++
using AIAC::EventPolicy::PrioriQueueListtyQueue =  std::priority_queue<Item, std::vector<Item>, EventCompare>;
```




<hr>
## Public Static Functions Documentation




### function GetCategory 

```C++
static inline EventCategory AIAC::EventPolicy::GetCategory (
    const EventPointer & event
) 
```




<hr>



### function GetEvent 

```C++
static inline EventType AIAC::EventPolicy::GetEvent (
    const EventPointer & event
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/Event.h`

