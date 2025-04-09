

# File CutPlaneVisualizer.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**Feedback**](dir_2e808e595a766fe55342199a604574e7.md) **>** [**CutPlaneVisualizer.h**](CutPlaneVisualizer_8h.md)

[Go to the documentation of this file](CutPlaneVisualizer_8h.md)


```C++
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
#ifndef CUTPLANEVISUALIZER_H
#define CUTPLANEVISUALIZER_H

#include "FeedbackVisualizer.h"
#include "utils/GeometryUtils.h"

namespace AIAC{
    class CutPlaneVisualizer : public FeedbackVisualizer {
    public:
        CutPlaneVisualizer();
        void Activate() override;
        void Deactivate() override;

        std::vector<glm::vec3> Update(glm::vec3 faceNorm, glm::vec3 facePt);

    private:  
        void ReorderIntersectPoints(std::vector<glm::vec3>& intersectPts, const glm::vec3& facePt);


    protected:
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAppCenterA;
        std::shared_ptr<GOLine> m_LongestIntersectSegmentAppCenterB;
        std::shared_ptr<GOLine> m_LongestIntersectSegmentA1;
        std::shared_ptr<GOLine> m_LongestIntersectSegmentA2;
        std::shared_ptr<GOLine> m_LongestIntersectSegmentB1;
        std::shared_ptr<GOLine> m_LongestIntersectSegmentB2;
    };
}

#endif // CUTPLANEVISUALIZER_H
```


