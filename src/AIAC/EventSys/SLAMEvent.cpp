#include "aiacpch.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"


namespace AIAC
{
    void SLAMMapLoadedEvent::OnSLAMMapLoaded()
    {
        AIAC_APP.GetLayer<LayerSlam>()->DummyRestart(m_FilePath);
        AIAC_WARN(m_FilePath);
    }

    void SLAMVocabularyLoadedEvent::OnSLAMVocabularyLoaded()
    {
        AIAC_APP.GetLayer<LayerSlam>()->DummyRestart(m_FilePath);
        AIAC_WARN(m_FilePath);
    }
}