#pragma once

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/EventSys/CameraEvent.h"


namespace AIAC
{
    using EQ = eventpp::EventQueue<EventType, void(const EventPointer&), EventPolicy>;
    class EventBus
    {
    public:
        ~EventBus() = default;

        void Init()
        {
            m_EventQueue.appendListener(EventType::SLAMMapLoaded, [](const EventPointer& event) {
                auto& slamEvent = static_cast<SLAMMapLoadedEvent&>(*event);
                slamEvent.OnSLAMMapLoaded();
            });
            m_EventQueue.appendListener(EventType::SLAMVocabularyLoaded, [](const EventPointer& event) {
                auto& slamEvent = static_cast<SLAMVocabularyLoadedEvent&>(*event);
                slamEvent.OnSLAMVocabularyLoaded();
            });
            m_EventQueue.appendListener(EventType::CameraCalibrationLoaded, [](const EventPointer& event) {
                auto& cameraEvent = static_cast<CameraCalibrationLoadedEvent&>(*event);
                cameraEvent.OnCameraCalibrationLoaded();
            });
        }

        void EnqueueEvent(const EventType & type, const EventPointer& sharedPtrEvent)
        {
            m_EventQueue.enqueue(type, sharedPtrEvent);
        }
        void EnqueueEvent(const EventPointer& sharedPtrEvent)
        {
            m_EventQueue.enqueue(sharedPtrEvent->GetType(), sharedPtrEvent);
        }

        // Asynchronus
        void ProcessQueue() { m_EventQueue.process(); }

        // Synchronus
        void DispatchEvent(const EventType & type, const EventPointer& sharedPtrEvent)
        {
            m_EventQueue.dispatch(type, sharedPtrEvent);
        }

    private:
        EQ m_EventQueue;
    };
}