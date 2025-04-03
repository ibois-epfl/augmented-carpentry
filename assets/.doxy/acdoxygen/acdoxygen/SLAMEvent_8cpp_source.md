

# File SLAMEvent.cpp

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**EventSys**](dir_bda428afb66b315b23b4e646d7591fb3.md) **>** [**SLAMEvent.cpp**](SLAMEvent_8cpp.md)

[Go to the documentation of this file](SLAMEvent_8cpp.md)


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
#include "aiacpch.h"
#include "AIAC/Config.h"
#include "AIAC/EventSys/SLAMEvent.h"
#include "AIAC/Application.h"
#include <filesystem>
#include <cstdlib>

namespace AIAC
{
    void SLAMMapLoadedEvent::OnSLAMMapLoaded()
    {
        AIAC_INFO("SLAM map file changed to: \"{}\"", m_FilePath);
        // update config
        AIAC::Config::UpdateEntry(AIAC::Config::SEC_TSLAM, AIAC::Config::MAP_FILE, m_FilePath);

        if(!std::filesystem::exists(m_FilePath)){
            AIAC_WARN("SLAM map file not found: \"{}\"", m_FilePath);
            return;
        }
        AIAC_APP.GetLayer<LayerSlam>()->UpdateMap(m_FilePath);

        // extract the camera calibration file path from the SLAM map and update for camera and SLAM
        auto paramHeight  = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CamSize.height;
        auto paramWidth   = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CamSize.width;
        auto cameraMatrix = AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap()->keyframes.begin()->imageParams.CameraMatrix;

        // update the camera parameters for camera
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromSlamMap(paramWidth, paramHeight, cameraMatrix);

        // update the camera parameters for SLAM
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CameraMatrix = cameraMatrix;
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CamSize.height = paramHeight;
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.CamSize.width = paramWidth;

        // update the camera parameters for TTool
        AIAC_APP.GetLayer<LayerToolhead>()->ReloadCameraFromMatrix(cameraMatrix, cv::Size(paramWidth, paramHeight));

        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();

        // enable SLAM
        AIAC_APP.GetLayer<LayerSlam>()->ToProcess = true;

        // TODO: Clean up the loaded mesh
    }

    void SLAMVocabularyLoadedEvent::OnSLAMVocabularyLoaded()
    {
        AIAC_INFO("SLAM vocabulary file changed to: {}", m_FilePath);

        // update config
        AIAC::Config::UpdateEntry(AIAC::Config::SEC_TSLAM, AIAC::Config::VocFile, m_FilePath);

        AIAC_APP.GetLayer<LayerSlam>()->Slam.setVocabulary(m_FilePath);
    }

    void SLAMStartMappingEvent::OnSLAMStartMapping()
    {
        AIAC_INFO("Start mapping");

        // update the camera parameters for SLAM
        auto camParamFilepath = AIAC::Config::Get<string>(
                AIAC::Config::SEC_AIAC,
                AIAC::Config::CAM_PARAMS_FILE,
                "assets/tslam/calibration_orange_A_1280_720_000B.yml");
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromFile(camParamFilepath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(camParamFilepath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));
        AIAC_APP.GetLayer<LayerToolhead>()->ReloadCameraFromFile();
        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();

        // start mapping
        AIAC_APP.GetLayer<AIAC::LayerSlam>()->StartMapping();
    }

    void SLAMStopMappingEvent::OnSLAMStopMapping()
    {
        // create folder
        auto path = m_SavePath.substr(0, m_SavePath.find_last_of("/"));
        auto folderCreatedSucceed = std::filesystem::create_directories(path);
        if(folderCreatedSucceed){
            AIAC_INFO("Create folder: {}", path);
        }

        AIAC_INFO("Stop mapping");
        AIAC_APP.GetLayer<AIAC::LayerSlam>()->StopMapping();

        // Optimize Map
        if(m_ToOptimize && m_ToSave) {
            AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->optimize();
        }
        
        // Save the map & reconstruct 3D
        if(m_ToSave) {
            auto basePath = m_SavePath.substr(0, m_SavePath.find_last_of("."));
            auto ymlTagMapPath = basePath + ".yml";
            auto recPlyPath = basePath + ".ply";

            AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToFile(m_SavePath);
            if(AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->map_markers.size() == 0){
                AIAC_WARN("No tag in the map, skip rest of the process");
                return;
            }
            AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToMarkerMap(ymlTagMapPath);
            
            // Reload Tag to GL for rendering
            AIAC_APP.GetLayer<AIAC::LayerSlam>()->InitSlamMapGOs();

            // Reconstruct 3D
            bool isReconstructed = AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.Reconstruct3DModelAndExportPly(
                ymlTagMapPath,
                recPlyPath,
                m_RadiusSearch,
                m_CreaseAngleThreshold,
                m_MinClusterSize,
                m_AABBScaleFactor,
                m_MaxPolyTagDist,
                m_MaxPlnDist2Merge,
                m_MaxPlnAngle2Merge,
                m_EPS
            );

            // Load reconstructed 3D model
            if(isReconstructed) AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadScannedModel(recPlyPath);
            else AIAC_WARN("Reconstruction failed, skip loading the model");
        }
    }

    void SLAMCombineMapEvent::OnSLAMCombineMap()
    {
        if (m_OutputPath.empty()) {
            auto basePathA = m_MapPathA.substr(0, m_MapPathA.find_last_of('.'));
            auto filenameB = m_MapPathB.substr(m_MapPathB.find_last_of('/') + 1);
            m_OutputPath = basePathA + "_combined_" + filenameB;
        }

        auto basePath = m_OutputPath.substr(0, m_OutputPath.find_last_of("."));
        auto ymlTagMapPath = basePath + ".yml";
        auto recPlyPath = basePath + "_reconstruct.ply";

        AIAC_APP.GetLayer<LayerSlam>()->Slam.CombineMap(
                m_MapPathA, m_MapPathB, m_OutputPath,
                true, true, nullptr, m_OptimizeIterations);

        // Reconstruct 3D
        bool isReconstructed = AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.Reconstruct3DModelAndExportPly(
                ymlTagMapPath,
                recPlyPath,
                m_RadiusSearch,
                m_CreaseAngleThreshold,
                m_MinClusterSize,
                m_AABBScaleFactor,
                m_MaxPolyTagDist,
                m_MaxPlnDist2Merge,
                m_MaxPlnAngle2Merge,
                m_EPS
        );

        // Load reconstructed 3D model
        if(isReconstructed) AIAC_APP.GetLayer<AIAC::LayerModel>()->LoadScannedModel(recPlyPath);
        else AIAC_WARN("Reconstruction failed, skip loading the model");
    }
}
```


