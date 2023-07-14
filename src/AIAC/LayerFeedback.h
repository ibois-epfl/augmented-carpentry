#pragma once

#include "AIAC/Layer.h"
#include "AIAC/ACInfoToolheadManager.h"
#include "AIAC/ACInfoToolhead.h"

namespace AIAC
{
    class LayerFeedback : public AIAC::Layer
    {
        public:
            LayerFeedback();
            virtual ~LayerFeedback() = default;

            virtual void OnAttach() override;
            virtual void OnFrameStart() override;

        // private:

            // -> current toolheaed
            // -> current model component to fabricate

            // translationFeedback
            // rotationFeedback

            // template <typename T>
            // inline std::shared_ptr<T> GetActiveToolheadData()
            // {
            //     return this->m_CurrentToolhead->GetData<T>();
            // }

        private:
            std::shared_ptr<ACInfoToolhead> m_CurrentToolhead;
            // obj current m_CurrentModelComponent;

    };
}