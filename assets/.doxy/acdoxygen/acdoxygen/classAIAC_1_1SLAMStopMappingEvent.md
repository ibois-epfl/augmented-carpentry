

# Class AIAC::SLAMStopMappingEvent



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**SLAMStopMappingEvent**](classAIAC_1_1SLAMStopMappingEvent.md)








Inherits the following classes: [AIAC::Event](classAIAC_1_1Event.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnSLAMStopMapping**](#function-onslamstopmapping) () <br> |
|   | [**SLAMStopMappingEvent**](#function-slamstopmappingevent) (bool toSave, std::string savePath, bool toOptimize, float radiusSearch, double creaseAngleThreshold, int minClusterSize, double AABBScaleFactor, double maxPolyTagDist, double maxPlnDist2Merge, double maxPlnAngle2Merge, double EPS) <br> |


## Public Functions inherited from AIAC::Event

See [AIAC::Event](classAIAC_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classAIAC_1_1Event.md#function-event) (const EventType type, const EventCategory category=EventCategory::None, int32\_t priority=0) <br> |
|  EventCategory | [**GetCategory**](classAIAC_1_1Event.md#function-getcategory) () const<br> |
|  EventType | [**GetType**](classAIAC_1_1Event.md#function-gettype) () const<br> |
| virtual  | [**~Event**](classAIAC_1_1Event.md#function-event) () = default<br> |






















































## Public Functions Documentation




### function OnSLAMStopMapping 

```C++
void AIAC::SLAMStopMappingEvent::OnSLAMStopMapping () 
```




<hr>



### function SLAMStopMappingEvent 

```C++
inline explicit AIAC::SLAMStopMappingEvent::SLAMStopMappingEvent (
    bool toSave,
    std::string savePath,
    bool toOptimize,
    float radiusSearch,
    double creaseAngleThreshold,
    int minClusterSize,
    double AABBScaleFactor,
    double maxPolyTagDist,
    double maxPlnDist2Merge,
    double maxPlnAngle2Merge,
    double EPS
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/SLAMEvent.h`

