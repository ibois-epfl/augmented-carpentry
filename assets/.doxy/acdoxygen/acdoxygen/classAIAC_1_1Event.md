

# Class AIAC::Event



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**Event**](classAIAC_1_1Event.md)










Inherited by the following classes: [AIAC::AppCloseEvent](classAIAC_1_1AppCloseEvent.md),  [AIAC::CameraCalibrationLoadedEvent](classAIAC_1_1CameraCalibrationLoadedEvent.md),  [AIAC::SLAMCombineMapEvent](classAIAC_1_1SLAMCombineMapEvent.md),  [AIAC::SLAMMapLoadedEvent](classAIAC_1_1SLAMMapLoadedEvent.md),  [AIAC::SLAMStartMappingEvent](classAIAC_1_1SLAMStartMappingEvent.md),  [AIAC::SLAMStopMappingEvent](classAIAC_1_1SLAMStopMappingEvent.md),  [AIAC::SLAMVocabularyLoadedEvent](classAIAC_1_1SLAMVocabularyLoadedEvent.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Event**](#function-event) (const EventType type, const EventCategory category=EventCategory::None, int32\_t priority=0) <br> |
|  EventCategory | [**GetCategory**](#function-getcategory) () const<br> |
|  EventType | [**GetType**](#function-gettype) () const<br> |
| virtual  | [**~Event**](#function-event) () = default<br> |




























## Public Functions Documentation




### function Event 

```C++
inline explicit AIAC::Event::Event (
    const EventType type,
    const EventCategory category=EventCategory::None,
    int32_t priority=0
) 
```




<hr>



### function GetCategory 

```C++
inline EventCategory AIAC::Event::GetCategory () const
```




<hr>



### function GetType 

```C++
inline EventType AIAC::Event::GetType () const
```




<hr>



### function ~Event 

```C++
virtual AIAC::Event::~Event () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/Event.h`

