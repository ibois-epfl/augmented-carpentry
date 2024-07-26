#pragma once

#include "AIAC/EventSys/Event.h"


namespace AIAC
{
    class SLAMMapLoadedEvent : public Event
    {
    public:
        explicit SLAMMapLoadedEvent(const std::string filePath)
            : Event(EventType::SLAMMapLoaded, EventCategory::EventCategorySLAM), m_FilePath(filePath)
        {}

        void OnSLAMMapLoaded();

    private:
        std::string m_FilePath;
    };

    class SLAMVocabularyLoadedEvent : public Event
    {
    public:
        explicit SLAMVocabularyLoadedEvent(const std::string filePath)
            : Event(EventType::SLAMVocabularyLoaded, EventCategory::EventCategorySLAM), m_FilePath(filePath)
        {}

        void OnSLAMVocabularyLoaded();
    
    private:
        std::string m_FilePath;
    };

    class SLAMStartMappingEvent : public Event
    {
    public:
        explicit SLAMStartMappingEvent()
            : Event(EventType::SLAMStartMapping, EventCategory::EventCategorySLAM)
        {}

        void OnSLAMStartMapping();
    };

    class SLAMStopMappingEvent : public Event
    {
    public:
        // FIXME: This is a bit ugly, creating a struct for the two sets of parameters may be better?
        explicit SLAMStopMappingEvent(// Save Map Parameters
                                      bool toSave,
                                      std::string savePath,
                                      bool toOptimize,
                                      // Reconstruction Parameters
                                      float radiusSearch,
                                      double creaseAngleThreshold,
                                      int minClusterSize,
                                      double AABBScaleFactor,
                                      double maxPolyTagDist,
                                      double maxPlnDist2Merge,
                                      double maxPlnAngle2Merge,
                                      double EPS)

            : Event(EventType::SLAMStopMapping, EventCategory::EventCategorySLAM),
            m_ToSave(toSave), m_SavePath(savePath), m_ToOptimize(toOptimize),
            m_RadiusSearch(radiusSearch), m_CreaseAngleThreshold(creaseAngleThreshold),
            m_MinClusterSize(minClusterSize), m_AABBScaleFactor(AABBScaleFactor),
            m_MaxPolyTagDist(maxPolyTagDist), m_MaxPlnDist2Merge(maxPlnDist2Merge),
            m_MaxPlnAngle2Merge(maxPlnAngle2Merge), m_EPS(EPS)
        {}

        void OnSLAMStopMapping();
    
    private:
        // Save Map Parameters
        bool m_ToSave;
        std::string m_SavePath;
        bool m_ToOptimize;

        // Reconstruction Parameters
        float m_RadiusSearch;
        double m_CreaseAngleThreshold;
        int m_MinClusterSize;
        double m_AABBScaleFactor;
        double m_MaxPolyTagDist;
        double m_MaxPlnDist2Merge;
        double m_MaxPlnAngle2Merge;
        double m_EPS;
    };

    class SLAMCombineMapEvent : public Event
    {
    public:
        // FIXME: This is a bit ugly, creating a struct for the two sets of parameters may be better?
        explicit SLAMCombineMapEvent(
                // Combine Map Parameters
                std::string mapPathA,
                std::string mapPathB,
                std::string outputPath,
                int optimizeIterations,

                // Reconstruction Parameters
                float radiusSearch,
                double creaseAngleThreshold,
                int minClusterSize,
                double AABBScaleFactor,
                double maxPolyTagDist,
                double maxPlnDist2Merge,
                double maxPlnAngle2Merge,
                double EPS)

                : Event(EventType::SLAMCombineMapEvent, EventCategory::EventCategorySLAM),
                  m_MapPathA(std::move(mapPathA)), m_MapPathB(std::move(mapPathB)), m_OutputPath(std::move(outputPath)),
                  m_OptimizeIterations(optimizeIterations),
                  m_RadiusSearch(radiusSearch), m_CreaseAngleThreshold(creaseAngleThreshold),
                  m_MinClusterSize(minClusterSize), m_AABBScaleFactor(AABBScaleFactor),
                  m_MaxPolyTagDist(maxPolyTagDist), m_MaxPlnDist2Merge(maxPlnDist2Merge),
                  m_MaxPlnAngle2Merge(maxPlnAngle2Merge), m_EPS(EPS)
        {}

        void OnSLAMCombineMap();

    private:
        // Combine Map Parameters
        std::string m_MapPathA;
        std::string m_MapPathB;
        std::string m_OutputPath;
        int m_OptimizeIterations;

        // Reconstruction Parameters
        float m_RadiusSearch;
        double m_CreaseAngleThreshold;
        int m_MinClusterSize;
        double m_AABBScaleFactor;
        double m_MaxPolyTagDist;
        double m_MaxPlnDist2Merge;
        double m_MaxPlnAngle2Merge;
        double m_EPS;
    };
}