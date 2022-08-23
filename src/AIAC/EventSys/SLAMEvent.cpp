#include "aiacpch.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"


namespace AIAC
{
    void SLAMMapLoadedEvent::OnSLAMMapLoaded()
    {
        AIAC_INFO("SLAM map file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setMap(m_FilePath);
    }

    void SLAMVocabularyLoadedEvent::OnSLAMVocabularyLoaded()
    {
        AIAC_INFO("SLAM vocabulary file changed to: {}", m_FilePath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setVocabulary(m_FilePath);
    }
}