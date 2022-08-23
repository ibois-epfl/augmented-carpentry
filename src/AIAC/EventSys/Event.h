#pragma once

#include "AIAC/Base.h"
#include "eventpp/include/eventpp/eventqueue.h"
#include "eventpp/include/eventpp/eventdispatcher.h"
#include "eventpp/include/eventpp/eventpolicies.h"



namespace AIAC
{
    enum class EventType
    {
        None = 0,
        AppClose,
        SLAMMapLoaded, SLAMVocabularyLoaded,
        CameraCalibrationLoaded
        /* add types of events here */
    };

    // enum EventCategory
    // {
    //     None = 0,
    //     EventCategoryApplication = BIT(0),
    //     EventCategorySLAM = BIT(1)
    //     /* add event category here */
    // };


// #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
//                                 virtual EventType GetType() const override { return GetStaticType(); }\
//                                 virtual const char* GetName() const override { return #type; }
// #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    // class Event
    // {
    // public:
    //     virtual ~Event() = default;

    //     virtual EventType GetType() const = 0;
    //     virtual const char* GetName() const = 0;
    //     virtual int GetCategoryFlags() const = 0;
    //     virtual std::string ToString() const { return GetName(); }

    //     inline bool IsInCategory(EventCategory category) const
    //     {
    //         return GetCategoryFlags() & category;
    //     }
    // };

    class Event
    {
    public:
        explicit Event(const EventType type) : m_Type(type) {}
        virtual ~Event() = default;

        EventType GetType() const { return m_Type; }

    private:
        EventType m_Type;
    };

    using EventPointer = std::shared_ptr<Event>;

    struct EventPolicy
    {
        static EventType GetEvent(const EventPointer& event) {
            return event->GetType();
        }
    };




    // using EQ = eventpp::EventQueue<EventType, void(const EventPointer&), EventPolicy>;
    // class EventBus
    // {
    // public:

    //     EventBus()
    //     { 
    //         s_Instance = this;
    //     }

    //     ~EventBus()
    //     {
    //         s_Instance = nullptr;
    //     }

    //     inline static EventBus& GetInstance() { return *s_Instance; } //???
    //     inline EQ& GetEventQueue() const { return m_EventQueue; }

    //     template<typename T>
    //     void AppendListener(std::function<void(const EventPointer&)> listener)
    //     {
    //         m_EventQueue.appendListener(T, listener);
    //     }

    //     template<typename T>
    //     void AppendListener(std::function<void(const EventPointer&)> listener)
    //     {
    //         m_EventQueue.appendListener(T::GetStaticType(), listener);
    //     }

    //     template<typename T>
    //     void Enqueue(const T& sharedPtrEvent)
    //     {
    //         m_EventQueue.enqueue(sharedPtrEvent);
    //     }

    //     // Asynchronus
    //     void ProcessQueue() { m_EventQueue.process(); }

    //     // Synchronus
    //     template<typename T>
    //     void Dispatch(const T& sharedPtrEvent)
    //     {
    //         m_EventQueue.dispatch(sharedPtrEvent);
    //     }

    //     template<typename T>
    //     void Dispatch(const EventType & type, const T& sharedPtrEvent)
    //     {
    //         m_EventQueue.dispatch(type, sharedPtrEvent);
    //     }

    // private:
    //     static EventBus* s_Instance;
    //     static EQ m_EventQueue;
    // };

    // #define AIAC_EBUS AIAC::EventBus::GetInstance()

}