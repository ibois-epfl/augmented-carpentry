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
#include "aiacpch.h"

#include "Config.h"
#include "AIAC/LayerModel.h"
#include "AIAC/GOSys/GO.h"
#include "AIAC/Application.h"
#include "AIAC/DLoader.h"
#include "GeometryUtils.h"
#include "glm/gtx/string_cast.hpp"

//TODO: add the 3D model importer

namespace AIAC
{
    LayerModel::LayerModel() {}
    
    void LayerModel::OnAttach()
    {
        m_ACInfoModelPath = AIAC::Config::Get<std::string>(
                AIAC::Config::SEC_AIAC,
                AIAC::Config::AC_INFO_MODEL,
                "assets/ACModel/test.acim");
        m_ScannedModelPath = AIAC::Config::Get<std::string>(
                AIAC::Config::SEC_AIAC,
                AIAC::Config::SCANNED_MODEL,
                "assets/ACModel/28_scanned_model.ply");
        m_AlignOffset = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::ALIGN_OFFSET, 0.0f);
        m_AlignRotation = AIAC::Config::Get<int>(AIAC::Config::SEC_AIAC, AIAC::Config::ALIGN_ROTATION, 0);
        m_AlignFlip = AIAC::Config::Get<bool>(AIAC::Config::SEC_AIAC, AIAC::Config::ALIGN_FLIP, false);

        bool acimLoaded = m_ACInfoModel.Load(m_ACInfoModelPath);
        bool scannedModelLoaded = m_ScannedModel.Load(m_ScannedModelPath);
        if(!acimLoaded || !scannedModelLoaded){
            AIAC_ERROR("LayerModel::OnAttach() failed to load models");
            return;
        }
        AlignModels();
    }
    
    void LayerModel::OnFrameStart() {}

    void LayerModel::LoadACInfoModel(const std::string &path)
    {
        bool succeed = m_ACInfoModel.Load(path);
        if(succeed){
            m_ACInfoModelPath = path;
            m_ACIMTransformMat = glm::mat4(1.0f);

            AIAC::Config::UpdateEntry<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config:: AC_INFO_MODEL, path);
            AlignModels();
        }
    }

    void LayerModel::LoadScannedModel(const std::string& path)
    {
        bool succeed = m_ScannedModel.Load(path);
        if(succeed) {
            m_ScannedModelPath = path;
            m_ACIMTransformMat = glm::mat4(1.0f);

            AIAC::Config::UpdateEntry<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config:: SCANNED_MODEL, path);
            
            AlignModels();
            AIAC_INFO("Scanned model from path: " + path + " is loaded and alligned.");
        }
    }

    void LayerModel::ReloadACInfoModel()
    {
        std::string path = AIAC::Config::Get<std::string>(
                AIAC::Config::SEC_AIAC, AIAC::Config::AC_INFO_MODEL, "assets/ACModel/test.acim");
        if(!std::filesystem::exists(path))
        {
            AIAC_WARN("LayerModel::ReloadACInfoModel()from path: " + path + " failed to load models");
            return;
        }
        bool succeed = m_ACInfoModel.Load(path);
        m_ACIMTransformMat = glm::mat4(1.0f);
        if (!succeed)
        {
            AIAC_WARN("LayerModel::ReloadACInfoModel() from path: " + path + " failed to load models");
            return;
        }
        AIAC_INFO("ACIM model from path: " + path + " is loaded.");
        AlignModels();
    }

    void LayerModel::AlignModels() {
        bool acimLoaded = m_ACInfoModel.Load(m_ACInfoModelPath);
        bool scannedModelLoaded = m_ScannedModel.Load(m_ScannedModelPath);
        m_ACIMTransformMat = glm::mat4(1.0f);

        auto acInfoModelBbox = m_ACInfoModel.GetTimberInfo().GetBoundingBox();
        auto scannedModelBbox = m_ScannedModel.GetBoundingBox();

        float infoModelLength = m_ACInfoModel.GetLength();
        float scannedModelLength = m_ScannedModel.GetLength();
        
        auto subBbox = m_ScannedModel.GetBoundingBox();
        if(m_AlignOffset > 0){
            auto usedPortion = (scannedModelLength - m_AlignOffset) / scannedModelLength;;
            subBbox[0] = (subBbox[0] - subBbox[1]) * usedPortion + subBbox[1];
            subBbox[3] = (subBbox[3] - subBbox[2]) * usedPortion + subBbox[2];
            subBbox[4] = (subBbox[4] - subBbox[5]) * usedPortion + subBbox[5];
            subBbox[7] = (subBbox[7] - subBbox[6]) * usedPortion + subBbox[6];
        }
        else if (m_AlignOffset < 0){
            auto usedPortion = (scannedModelLength + m_AlignOffset) / scannedModelLength;;
            subBbox[1] = (subBbox[1] - subBbox[0]) * usedPortion + subBbox[0];
            subBbox[2] = (subBbox[2] - subBbox[3]) * usedPortion + subBbox[3];
            subBbox[5] = (subBbox[5] - subBbox[4]) * usedPortion + subBbox[4];
            subBbox[6] = (subBbox[6] - subBbox[7]) * usedPortion + subBbox[7];
        } else {
            auto usedPortion = (scannedModelLength + m_AlignOffset) / scannedModelLength;;
            subBbox[1] = (subBbox[1] - subBbox[0]) * usedPortion + subBbox[0];
            subBbox[2] = (subBbox[2] - subBbox[3]) * usedPortion + subBbox[3];
            subBbox[5] = (subBbox[5] - subBbox[4]) * usedPortion + subBbox[4];
            subBbox[6] = (subBbox[6] - subBbox[7]) * usedPortion + subBbox[7];
        }

        // rotate the subBox
        for(int i = 0 ; i < m_AlignRotation; i++){
            auto tmp = subBbox[0];
            subBbox[0] = subBbox[4];
            subBbox[4] = subBbox[7];
            subBbox[7] = subBbox[3];
            subBbox[3] = tmp;

            tmp = subBbox[1];
            subBbox[1] = subBbox[5];
            subBbox[5] = subBbox[6];
            subBbox[6] = subBbox[2];
            subBbox[2] = tmp;
        }
        // flip the subBox
        if(m_AlignFlip){
            std::swap(subBbox[0], subBbox[5]);
            std::swap(subBbox[1], subBbox[4]);
            std::swap(subBbox[2], subBbox[7]);
            std::swap(subBbox[3], subBbox[6]);
        }

        m_ACIMTransformMat = GetRigidTransformationMatrix(acInfoModelBbox, subBbox);
        m_ACInfoModel.Transform(m_ACIMTransformMat);
    }
}