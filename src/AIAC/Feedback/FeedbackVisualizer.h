//
// Created by ibois on 7/28/23.
//

#ifndef AC_FEEDBACKVISUALIZER_H
#define AC_FEEDBACKVISUALIZER_H

#include "vector"
#include "memory"
#include "AIAC/GOSys/GOPrimitive.h"
#include "AIAC/Config.h"

namespace AIAC{
    class FeedbackVisualizer {
    public:
        FeedbackVisualizer() = default;
        ~FeedbackVisualizer() = default;

        inline virtual void Activate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(true);
            }
        }

        inline virtual void Deactivate() {
            for (auto &p : m_AllPrimitives) {
                p->SetVisibility(false);
            }
        }

        /**
         * @brief Convert a double value to the real world scale in mm and return a string with 2 digits.
         * If the value in mm is > 99, return "99"
         * 
        */
        static std::string toString(double val) {
            // TODO: / 50 * 1000 => convert to right scale in mm, change this to a variable based on config
            auto scale = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 0.0f);
            int valInt = (int)(val / scale * 1000);
            if(valInt > 99) valInt = 99;
            auto retVal = std::to_string(valInt);
            if(retVal.length() == 1){
                return "0" + retVal;
            }
            return retVal;
        }

    protected:
        std::vector<std::shared_ptr<GOPrimitive>> m_AllPrimitives;
    };

    
}

#endif //AC_FEEDBACKVISUALIZER_H
