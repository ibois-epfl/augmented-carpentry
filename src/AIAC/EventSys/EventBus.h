#pragma once

#include "AIAC/EventSys/Event.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/EventSys/CameraEvent.h"
#include "AIAC/EventSys/ApplicationEvent.h"


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
            m_EventQueue.appendListener(EventType::SLAMStartMapping, [](const EventPointer& event) {
                auto& slamEvent = static_cast<SLAMStartMappingEvent&>(*event);
                slamEvent.OnSLAMStartMapping();
            });
            m_EventQueue.appendListener(EventType::SLAMStopMapping, [](const EventPointer& event) {
                auto& slamEvent = static_cast<SLAMStopMappingEvent&>(*event);
                slamEvent.OnSLAMStopMapping();
            });
            m_EventQueue.appendListener(EventType::SLAMCombineMapEvent, [](const EventPointer& event) {
                auto& slamEvent = static_cast<SLAMCombineMapEvent&>(*event);
                slamEvent.OnSLAMCombineMap();
            });
            m_EventQueue.appendListener(EventType::CameraCalibrationLoaded, [](const EventPointer& event) {
                auto& cameraEvent = static_cast<CameraCalibrationLoadedEvent&>(*event);
                cameraEvent.OnCameraCalibrationFileLoaded();
            });
            m_EventQueue.appendListener(EventType::AppClose, [](const EventPointer& event) {
                auto& appEvent = static_cast<AppCloseEvent&>(*event);
                appEvent.OnAppClose();
            });
        }

        void EnqueueEvent(const EventPointer& sharedPtrEvent)
        {
            m_EventQueue.enqueue(sharedPtrEvent->GetType(), sharedPtrEvent);
        }

        // Asynchronus
        void ProcessQueue() { m_EventQueue.process(); }

        // Synchronus
        void DispatchEvent(const EventPointer& sharedPtrEvent)
        {
            m_EventQueue.dispatch(sharedPtrEvent->GetType(), sharedPtrEvent);
        }

        inline bool IsEventQueueEmpty() const { return m_EventQueue.emptyQueue(); }

    private:
        EQ m_EventQueue;
    };
}