#pragma once

#include "AIAC/EventSys/Event.h"


// namespace AIAC
// {
//     class SLAMEvent : public Event
//     {
//     public:
//         explicit SLAMEvent(const std::string mapPath)
//             : Event(EventType::SLAMMapLoaded), m_MapPath(mapPath)
//         {}
//         explicit SLAMEvent(const std::string vocabularyPath)
//             : Event(EventType::SLAMVocabularyLoaded), m_VocabularyPath(vocabularyPath)
//         {}
//         explicit SLAMEvent(const std::string cameraCalibrationPath)
//             : Event(EventType::CameraCalibrationLoaded), m_CameraCalibrationPath(cameraCalibrationPath)
//         {}

//         inline const std::string& GetMapPath() const { return m_MapPath; }
//         inline const std::string& GetVocabularyPath() const { return m_VocabularyPath; }
//         inline const std::string& GetCameraCalibrationPath() const { return m_CameraCalibrationPath; }

//         AIAC_EQ.AppendListener(EventType::SLAMMapLoaded, [](const EventPointer& event)
//         {
//             const auto& slamEvent = std::static_pointer_cast<SLAMEvent>(event);
//             AIAC_LOG(Info, "SLAM map loaded: {}", slamEvent->GetMapPath());
//         };

//     private:
//         std::string m_MapPath;
//         std::string m_VocabularyPath;
//         std::string m_CameraCalibrationPath;
//     };
// }