#include "CutBladeThicknessVisualizer.h"
#include "AIAC/Application.h"


namespace AIAC
{
    CutBladeThicknessVisualizer::CutBladeThicknessVisualizer()
    {
        this->m_LongestIntersectSegmenDetectToolPlane = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentTowardsCameraA = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentTowardsCameraB = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentAwayFromCameraA = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentAwayFromCameraB = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_LongestIntersectSegmenDetectToolPlane->SetWeight(GOWeight::Light);
        this->m_LongestIntersectSegmentTowardsCameraA->SetWeight(GOWeight::Light);
        this->m_LongestIntersectSegmentTowardsCameraB->SetWeight(GOWeight::Light);
        this->m_LongestIntersectSegmentAwayFromCameraA->SetWeight(GOWeight::Light);
        this->m_LongestIntersectSegmentAwayFromCameraB->SetWeight(GOWeight::Light);

        this->m_LongestIntersectSegmenDetectToolPlane->SetColor(GOColor::CYAN);
        this->m_LongestIntersectSegmentTowardsCameraA->SetColor(GOColor::RED);
        this->m_LongestIntersectSegmentTowardsCameraB->SetColor(GOColor::RED);
        this->m_LongestIntersectSegmentAwayFromCameraA->SetColor(GOColor::RED);
        this->m_LongestIntersectSegmentAwayFromCameraB->SetColor(GOColor::RED);

        this->m_LongestIntersectSegmenDetectToolPlane->SetVisibility(IsSegmenDetectToolPlaneVisible);

        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmenDetectToolPlane);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentTowardsCameraA);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentTowardsCameraB);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentAwayFromCameraA);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentAwayFromCameraB);

        this->Deactivate();
    }
} // namespace AIAC