//
// Created by ibois on 7/28/23.
//

#ifndef AC_FEEDBACKVISUALIZER_H
#define AC_FEEDBACKVISUALIZER_H

#include "vector"
#include "memory"
#include "AIAC/GOSys/GOPrimitive.h"

namespace AIAC{
    class FeedbackVisualizer {
    public:
        FeedbackVisualizer() = default;
        ~FeedbackVisualizer() = default;

        inline void Activate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(true);
            }
        }

        inline void Deactivate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(false);
            }
        }

    protected:
        std::vector<std::shared_ptr<GOPrimitive>> m_AllPrimitives;
    };
}

#endif //AC_FEEDBACKVISUALIZER_H
