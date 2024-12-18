// #####################################################################
// >>>>>>>>>>>>>>>>>>>>> BEGINNING OF LEGAL NOTICE >>>>>>>>>>>>>>>>>>>>>
//######################################################################
//
// This source file, along with its associated content, was authored by
// Andrea Settimi, Hong-Bin Yang, Naravich Chutisilp, and numerous other
// contributors. The code was originally developed at the Laboratory for
// Timber Construction (IBOIS, director: Prof. Yves Weinand) at the School of 
// Architecture, Civil and Environmental Engineering (ENAC) at the Swiss
// Federal Institute of Technology in Lausanne (EPFL) for the Doctoral
// Research "Augmented Carpentry" (PhD researcher: Andrea Settimi,
// co-director: Dr. Julien Gamerro, director: Prof. Yves Weinand).
//
// Although the entire repository is distributed under the GPL license,
// these particular source files may also be used under the terms of the
// MIT license. By accessing or using this file, you agree to the following:
//
// 1. You may reproduce, modify, and distribute this file in accordance
//    with the terms of the MIT license.
// 2. You must retain this legal notice in all copies or substantial
//    portions of this file.
// 3. This file is provided "AS IS," without any express or implied
//    warranties, including but not limited to the implied warranties of
//    merchantability and fitness for a particular purpose.
//
// If you cannot or will not comply with the above conditions, you are
// not permitted to use this file. By proceeding, you acknowledge and
// accept all terms and conditions herein.
//
//######################################################################
// <<<<<<<<<<<<<<<<<<<<<<< END OF LEGAL NOTICE <<<<<<<<<<<<<<<<<<<<<<<<
// #####################################################################
//
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