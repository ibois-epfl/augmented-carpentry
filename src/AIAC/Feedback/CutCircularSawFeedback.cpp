//
// Created by ibois on 7/28/23.
//

#include "CutCircularSawFeedback.h"

namespace AIAC {
    CutCircularSawFeedbackVisualizer::CutCircularSawFeedbackVisualizer() {
        m_LineBottom = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineSide1 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));
        m_LineSide2 = GOLine::Add(GOPoint(0.f, 0.f, 0.f), GOPoint(0.f, 0.f, 0.f));

        m_LineBottom->SetColor(GOColor::CYAN);
        m_LineSide1->SetColor(GOColor::YELLOW);
        m_LineSide2->SetColor(GOColor::YELLOW);

        m_AllPrimitives.push_back(m_LineBottom);
        m_AllPrimitives.push_back(m_LineSide1);
        m_AllPrimitives.push_back(m_LineSide2);

        Deactivate();
    }

    CutCircularSawFeedback::CutCircularSawFeedback() {
        
    }


}