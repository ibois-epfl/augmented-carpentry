

# Class AIAC::CameraCalibrationLoadedEvent



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**CameraCalibrationLoadedEvent**](classAIAC_1_1CameraCalibrationLoadedEvent.md)








Inherits the following classes: [AIAC::Event](classAIAC_1_1Event.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CameraCalibrationLoadedEvent**](#function-cameracalibrationloadedevent) (const std::string filePath) <br> |
|  void | [**OnCameraCalibrationFileLoaded**](#function-oncameracalibrationfileloaded) () <br> |


## Public Functions inherited from AIAC::Event

See [AIAC::Event](classAIAC_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classAIAC_1_1Event.md#function-event) (const EventType type, const EventCategory category=EventCategory::None, int32\_t priority=0) <br> |
|  EventCategory | [**GetCategory**](classAIAC_1_1Event.md#function-getcategory) () const<br> |
|  EventType | [**GetType**](classAIAC_1_1Event.md#function-gettype) () const<br> |
| virtual  | [**~Event**](classAIAC_1_1Event.md#function-event) () = default<br> |






















































## Public Functions Documentation




### function CameraCalibrationLoadedEvent 

```C++
inline explicit AIAC::CameraCalibrationLoadedEvent::CameraCalibrationLoadedEvent (
    const std::string filePath
) 
```




<hr>



### function OnCameraCalibrationFileLoaded 

```C++
void AIAC::CameraCalibrationLoadedEvent::OnCameraCalibrationFileLoaded () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/CameraEvent.h`

