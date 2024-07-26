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
        auto camParamFilepath = AIAC::Config::Get<string>(AIAC::Config::SEC_AIAC, AIAC::Config::CAM_PARAMS_FILE);
        AIAC_APP.GetLayer<LayerCamera>()->MainCamera.UpdateCameraParamFromFile(camParamFilepath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.setCamParams(camParamFilepath);
        AIAC_APP.GetLayer<LayerSlam>()->Slam.imageParams.Distorsion.setTo(cv::Scalar::all(0));
        AIAC_APP.GetLayer<LayerToolhead>()->ReloadCameraFromFile();
        // update projection matrix
        AIAC_APP.GetRenderer()->InitProjMatrix();

        // start mapping
        AIAC_APP.GetLayer<AIAC::LayerSlam>()->StartMapping();
        AIAC_APP.GetRenderer()->StartMapping();
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
        AIAC_APP.GetRenderer()->StopMapping();

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

        // FIXME: nasty workaround
        string command = "tslam_combine_map ";
        command += m_MapPathA + " " + m_MapPathB + " " + m_OutputPath;
        std::system(command.c_str());

        auto basePath = m_OutputPath.substr(0, m_OutputPath.find_last_of("."));
        auto ymlTagMapPath = basePath + ".yml";
        auto recPlyPath = basePath + ".ply";

        /// FIXME: Some tag disappears after combining maps, don't know why
//        AIAC_APP.GetLayer<LayerSlam>()->Slam.CombineMap(
//                m_MapPathA, m_MapPathB, m_OutputPath,
//                false, false, nullptr, m_OptimizeIterations);
//
//        AIAC_APP.GetLayer<LayerSlam>()->UpdateMap(m_OutputPath);
//
//        AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->saveToFile(ymlTagMapPath);
//        if(AIAC_APP.GetLayer<AIAC::LayerSlam>()->Slam.getMap()->map_markers.size() == 0){
//            AIAC_WARN("No tag in the map, skip rest of the process");
//            return;
//        }

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