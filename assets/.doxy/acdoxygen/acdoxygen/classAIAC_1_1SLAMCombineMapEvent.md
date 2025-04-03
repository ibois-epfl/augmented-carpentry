

# Class AIAC::SLAMCombineMapEvent



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**SLAMCombineMapEvent**](classAIAC_1_1SLAMCombineMapEvent.md)








Inherits the following classes: [AIAC::Event](classAIAC_1_1Event.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnSLAMCombineMap**](#function-onslamcombinemap) () <br> |
|   | [**SLAMCombineMapEvent**](#function-slamcombinemapevent) (std::string mapPathA, std::string mapPathB, std::string outputPath, int optimizeIterations, float radiusSearch, double creaseAngleThreshold, int minClusterSize, double AABBScaleFactor, double maxPolyTagDist, double maxPlnDist2Merge, double maxPlnAngle2Merge, double EPS) <br> |


## Public Functions inherited from AIAC::Event

See [AIAC::Event](classAIAC_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classAIAC_1_1Event.md#function-event) (const EventType type, const EventCategory category=EventCategory::None, int32\_t priority=0) <br> |
|  EventCategory | [**GetCategory**](classAIAC_1_1Event.md#function-getcategory) () const<br> |
|  EventType | [**GetType**](classAIAC_1_1Event.md#function-gettype) () const<br> |
| virtual  | [**~Event**](classAIAC_1_1Event.md#function-event) () = default<br> |






















































## Public Functions Documentation




### function OnSLAMCombineMap 

```C++
void AIAC::SLAMCombineMapEvent::OnSLAMCombineMap () 
```




<hr>



### function SLAMCombineMapEvent 

```C++
inline explicit AIAC::SLAMCombineMapEvent::SLAMCombineMapEvent (
    std::string mapPathA,
    std::string mapPathB,
    std::string outputPath,
    int optimizeIterations,
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

