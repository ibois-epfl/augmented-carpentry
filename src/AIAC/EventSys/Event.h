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

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication =              BIT(0),
        EventCategorySLAM =                     BIT(1),
        EventCategoryCamera =                   BIT(2)
        /* add event category here */
    };

    class Event
    {
    public:
        explicit Event(const EventType type, const EventCategory category = EventCategory::None)
            : m_Type(type), m_Category(category)
        {}
        virtual ~Event() = default;

        EventType GetType() const { return m_Type; }
        EventCategory GetCategory() const { return m_Category; }

    private:
        EventType m_Type;
        EventCategory m_Category;
    };

    using EventPointer = std::shared_ptr<Event>;

    struct EventPolicy
    {
        static EventType GetEvent(const EventPointer& event) {
            return event->GetType();
        }
    };

}