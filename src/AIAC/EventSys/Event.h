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
        SLAMMapLoaded, SLAMVocabularyLoaded, SLAMStartMapping, SLAMStopMapping,
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
        explicit Event(const EventType type, const EventCategory category = EventCategory::None, int32_t priority = 0)
            : m_Type(type), m_Category(category), m_Priority(priority)
        {}
        virtual ~Event() = default;

        EventType GetType() const { return m_Type; }
        EventCategory GetCategory() const { return m_Category; }

    private:
        EventType m_Type;
        EventCategory m_Category;
        int32_t m_Priority;
    };

    using EventPointer = std::shared_ptr<Event>;

    struct EventCompare
    {
        template <typename T>
        bool operator() (const T & a, const T & b) const
        {
            return a->GetPriority() > b->GetPriority();
        }
    };

    struct EventPolicy
    {
        template <typename Item>
        using PrioriQueueListtyQueue = std::priority_queue<Item, std::vector<Item>, EventCompare>;

        static EventType GetEvent(const EventPointer& event) {
            return event->GetType();
        }

        static EventCategory GetCategory(const EventPointer& event) {
            return event->GetCategory();
        }
    };

}