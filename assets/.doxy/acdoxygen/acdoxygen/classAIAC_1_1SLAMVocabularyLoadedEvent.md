

# Class AIAC::SLAMVocabularyLoadedEvent



[**ClassList**](annotated.md) **>** [**AIAC**](namespaceAIAC.md) **>** [**SLAMVocabularyLoadedEvent**](classAIAC_1_1SLAMVocabularyLoadedEvent.md)








Inherits the following classes: [AIAC::Event](classAIAC_1_1Event.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnSLAMVocabularyLoaded**](#function-onslamvocabularyloaded) () <br> |
|   | [**SLAMVocabularyLoadedEvent**](#function-slamvocabularyloadedevent) (const std::string filePath) <br> |


## Public Functions inherited from AIAC::Event

See [AIAC::Event](classAIAC_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classAIAC_1_1Event.md#function-event) (const EventType type, const EventCategory category=EventCategory::None, int32\_t priority=0) <br> |
|  EventCategory | [**GetCategory**](classAIAC_1_1Event.md#function-getcategory) () const<br> |
|  EventType | [**GetType**](classAIAC_1_1Event.md#function-gettype) () const<br> |
| virtual  | [**~Event**](classAIAC_1_1Event.md#function-event) () = default<br> |






















































## Public Functions Documentation




### function OnSLAMVocabularyLoaded 

```C++
void AIAC::SLAMVocabularyLoadedEvent::OnSLAMVocabularyLoaded () 
```




<hr>



### function SLAMVocabularyLoadedEvent 

```C++
inline explicit AIAC::SLAMVocabularyLoadedEvent::SLAMVocabularyLoadedEvent (
    const std::string filePath
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/AIAC/EventSys/SLAMEvent.h`

