// #pragma once

// #include "AIAC/Base.h"
// #include "eventqueue.h"

// namespace AIAC
// {
//     enum class EventType
//     {
//         None = 0,
//         AppClose,
//         SLAMMapLoaded, SLAMVocabularyLoaded,
//         CameraCalibrationLoaded
//         /* add types of events here */
//     };

//     // enum EventCategory
//     // {
//     //     None = 0,
//     //     EventCategoryApplication = BIT(0),
//     //     EventCategorySLAM = BIT(1)
//     //     /* add event category here */
//     // };


// // #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
// //                                 virtual EventType GetType() const override { return GetStaticType(); }\
// //                                 virtual const char* GetName() const override { return #type; }
// // #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


//     // class Event
//     // {
//     // public:
//     //     virtual ~Event() = default;

//     //     virtual EventType GetType() const = 0;
//     //     virtual const char* GetName() const = 0;
//     //     virtual int GetCategoryFlags() const = 0;
//     //     virtual std::string ToString() const { return GetName(); }

//     //     inline bool IsInCategory(EventCategory category) const
//     //     {
//     //         return GetCategoryFlags() & category;
//     //     }
//     // };

//     class Event
//     {
//     public:
//         explicit Event(const EventType type) : m_Type(type) {}
//         virtual ~Event() = default;

//         EventType GetType() const { return m_Type; }

//     private:
//         EventType m_Type;
//     };

//     using EventPointer = std::shared_ptr<Event>;

//     struct EventPolicy
//     {
//         static EventType GetEvent(const EventPointer & event) {
//             return event->GetType();
//         }
//     };




//     using EQ = eventpp::EventQueue<EventType, void(const EventPointer &), EventPolicy>;
//     class EventManager
//     {
//     public:

//         EventManager()
//         { 
//             s_Instance = std::make_unique<EventManager>(this);  //???
//         }
//         ~EventManager()
//         {
//             s_Instance = nullptr;
//         }

//         static std::unique_ptr<EventManager>& Get() { return s_Instance; } //???
//         EQ GetEventQueue() const { return m_EventQueue; }


//         template<typename T>
//         void AppendListener(std::function<void(const EventPointer &)> listener)
//         {
//             m_EventQueue.AppendListener(T::GetStaticType(), listener);
//         }

//         template<typename T>
//         void Enqueue(const T & event)
//         {
//             m_EventQueue.Enqueue(event);
//         }


//         // ProcessQueue() will process all events in the queue and call the listeners
//         void ProcessQueue() { m_EventQueue.process(); }

//         // Dispatch() will dispatch events to the listeners directly
//         void Dispatch(const EventPointer & event) { m_EventQueue.dispatch(event); }
//         void Dispatch(const EventType & type, const EventPointer & event) { m_EventQueue.dispatch(type, event); }

//     private:
//         static std::unique_ptr<EventManager> s_Instance;
//         EQ m_EventQueue;
//     };

//     #define AIAC_EQ EventManager::Get().GetEventQueue()


// }