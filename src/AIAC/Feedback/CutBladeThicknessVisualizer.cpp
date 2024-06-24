#include "AIAC/Application.h"
#include "AIAC/Feedback/FabFeedback.h"
#include "AIAC/Feedback/CutBladeThicknessVisualizer.h"

namespace AIAC
{
    CutBladeThicknessVisualizer::CutBladeThicknessVisualizer()
    {
        this->m_LongestIntersectSegmentTowardsCamera = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentAwayFromCamera = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        this->m_LongestIntersectSegmentTToolPlane = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        this->m_LongestIntersectSegmentTowardsCamera->SetWeight(GOWeight::Light);
        this->m_LongestIntersectSegmentAwayFromCamera->SetWeight(GOWeight::Light);

        this->m_LongestIntersectSegmentTowardsCamera->SetColor(GOColor::RED);
        this->m_LongestIntersectSegmentTowardsCamera->SetColor(GOColor::RED);

        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentTowardsCamera);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentAwayFromCamera);
        this->m_AllPrimitives.push_back(this->m_LongestIntersectSegmentTToolPlane);

        this->Deactivate();
    }

    void CutBladeThicknessVisualizer::Activate()
    {
        this->Activate();
    }

    void CutBladeThicknessVisualizer::Deactivate()
    {
        this->Deactivate();
    }

    void CutBladeThicknessVisualizer::UpdateToolheadsData()
    {
        auto currentToolType = AIAC_APP.GetLayer<LayerToolhead>()->ACInfoToolheadManager->GetActiveToolheadType();
        if (currentToolType == ACToolHeadType::CHAINSAW) {
            this->bladeTotalThicknessScaled = AC_FF_TOOL->GetData<ChainSawData>().ThicknessACIT;
            this->bladeOverhangScaled = AC_FF_TOOL->GetData<ChainSawData>().OverhangACIT;
            this->m_ToolheadRefNormStart = AC_FF_TOOL->GetData<ChainSawData>().NormStartGO->GetPosition();
            this->m_ToolheadRefNormEnd = AC_FF_TOOL->GetData<ChainSawData>().NormEndGO->GetPosition();
            this->m_ToolheadRefCenter = AC_FF_TOOL->GetData<ChainSawData>().CenterGO->GetPosition();
        } else if (currentToolType == ACToolHeadType::CIRCULARSAW) {
            this->bladeTotalThicknessScaled = AC_FF_TOOL->GetData<CircularSawData>().ThicknessACIT;
            this->bladeOverhangScaled = AC_FF_TOOL->GetData<CircularSawData>().OverhangACIT;
            this->m_ToolheadRefNormStart = AC_FF_TOOL->GetData<CircularSawData>().NormStartGO->GetPosition();
            this->m_ToolheadRefNormEnd = AC_FF_TOOL->GetData<CircularSawData>().NormEndGO->GetPosition();
            this->m_ToolheadRefCenter = AC_FF_TOOL->GetData<ChainSawData>().CenterGO->GetPosition();
        } else {
            AIAC_WARN("Toolhead type not supported for thickness visualizer");
            return;
        }

        this->m_NormalUnitized = glm::normalize(this->m_ToolheadRefNormEnd - this->m_ToolheadRefNormStart);
        this->m_NormalOppositeUnitized = -this->m_NormalUnitized;
        this->m_DisplacedCenterTowardsCamera = this->m_ToolheadRefCenter + this->m_NormalUnitized * this->bladeThicknessScaled;
    }

    void CutBladeThicknessVisualizer::Update(AIAC::TimberInfo::Cut::Face activeFaceInfo)
    {
        this->UpdateToolheadsGOs();
    }
}