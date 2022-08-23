#pragma once

#include "AIAC/EventSys/Event.h"


namespace AIAC
{
    class CameraCalibrationLoadedEvent : public Event
    {
    public:
        explicit CameraCalibrationLoadedEvent(const std::string filePath)
            : Event(EventType::CameraCalibrationLoaded, EventCategory::EventCategoryCamera), m_FilePath(filePath)
        {}
        
        void OnCameraCalibrationLoaded();
    
    private:
        std::string m_FilePath;
    };
}