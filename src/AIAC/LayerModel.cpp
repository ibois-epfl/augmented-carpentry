#include "aiacpch.h"

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
        m_ACInfoModel.Load("assets/ACModel/test.acim");
        m_ScannedModel.Load("assets/ACModel/01_scanned_model.ply");
        AlignModels();
    }
    
    void LayerModel::OnFrameStart()
    {


    }

    void LayerModel::AlignModels() {
        auto acInfoModelBbox = m_ACInfoModel.GetActiveTimberInfo().GetBoundingBox();
        auto scannedModelBbox = m_ScannedModel.GetBoundingBox();

        float infoModelLength = m_ACInfoModel.GetLength();
        float scannedModelLength = m_ScannedModel.GetLength();

        AIAC_INFO("AC Info Model Length: {0} (m)", infoModelLength * 0.02);
        AIAC_INFO("Scanned Model Length: {0} (m)", scannedModelLength * 0.02);

        // crop the scanned model to the similar length as the info model
        // reserve 2 cm on each side = 4 cm = 0.04 m = 2 TSLAM unit (by * 50)
        auto usedPortion = (infoModelLength + 2) / scannedModelLength;
        auto subBbox = m_ScannedModel.GetBoundingBox();
        subBbox[1] = (subBbox[1] - subBbox[0]) * usedPortion + subBbox[0];
        subBbox[2] = (subBbox[2] - subBbox[3]) * usedPortion + subBbox[3];
        subBbox[5] = (subBbox[5] - subBbox[4]) * usedPortion + subBbox[4];
        subBbox[6] = (subBbox[6] - subBbox[7]) * usedPortion + subBbox[7];

        auto transMat = GetRigidTransformationMatrix(acInfoModelBbox, subBbox);
        m_ACInfoModel.TransformGOPrimitives(transMat);

    }
}