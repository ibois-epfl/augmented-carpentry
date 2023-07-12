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
        auto acInfoModelPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::AC_INFO_MODEL, "assets/ACModel/test.acim");
        auto scannedModelPath = AIAC::Config::Get<std::string>(AIAC::Config::SEC_AIAC, AIAC::Config::SCANNED_MODEL, "assets/ACModel/28_scanned_model.ply");
        m_ACInfoModel.Load(acInfoModelPath);
        m_ScannedModel.Load(scannedModelPath);
        AlignModels();
    }
    
    void LayerModel::OnFrameStart()
    {

    }

    void LayerModel::LoadACInfoModel(std::string path)
    {
        m_ACInfoModel.Load(path);
        AlignModels();
    }

    void LayerModel::LoadScannedModel(std::string path)
    {
        m_ScannedModel.Load(path);
        AlignModels();
    }

    void LayerModel::AlignModels() {
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
        } else {
            auto usedPortion = (scannedModelLength + m_AlignOffset) / scannedModelLength;;
            subBbox[1] = (subBbox[1] - subBbox[0]) * usedPortion + subBbox[0];
            subBbox[2] = (subBbox[2] - subBbox[3]) * usedPortion + subBbox[3];
            subBbox[5] = (subBbox[5] - subBbox[4]) * usedPortion + subBbox[4];
            subBbox[6] = (subBbox[6] - subBbox[7]) * usedPortion + subBbox[7];
        }

        auto transMat = GetRigidTransformationMatrix(acInfoModelBbox, subBbox);
        m_ACInfoModel.TransformGOPrimitives(transMat);
    }
}