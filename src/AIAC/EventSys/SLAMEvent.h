#pragma once

#include "AIAC/EventSys/Event.h"


namespace AIAC
{
    class SLAMMapLoadedEvent : public Event
    {
    public:
        explicit SLAMMapLoadedEvent(const std::string filePath)
            : Event(EventType::SLAMMapLoaded), m_FilePath(filePath)
        {}

        void OnSLAMMapLoaded();

    private:
        std::string m_FilePath;
    };

    class SLAMVocabularyLoadedEvent : public Event
    {
    public:
        explicit SLAMVocabularyLoadedEvent(const std::string filePath)
            : Event(EventType::SLAMVocabularyLoaded), m_FilePath(filePath)
        {}

        void OnSLAMVocabularyLoaded();
    
    private:
        std::string m_FilePath;
    };
}