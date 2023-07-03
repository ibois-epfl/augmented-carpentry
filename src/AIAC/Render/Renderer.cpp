#include "aiacpch.h"

#include "AIAC/Render/Renderer.h"
#include "TextRenderer.h"

#include "AIAC/Application.h"
#include "AIAC/Log.h"
#include "AIAC/Config.h"

#include "AIAC/Render/RenderAPI.h"
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.hpp"

#include "utils/utils.h"
#include "AIAC/LayerCameraCalib.h"

namespace AIAC
{
    void Renderer::Init()
    {
        // Create and compile our GLSL program from the shaders
        char* vertexFilePath = (char*)"assets/opengl/SimpleTransform.vs";
        char* fragmentFilePath = (char*)"assets/opengl/SingleColor.fs";

        m_BasicShaderProgram = LoadShaders(vertexFilePath, fragmentFilePath);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // Get a handle for our "MVP" uniform
        m_MatrixId = glGetUniformLocation(m_BasicShaderProgram, "MVP");

        // init the projection matrix based on the camera parameters
        InitProjMatrix();

        // Load meshes
        ReloadMeshes();

        // Initialize the static interface of TextRenderer
        TextRenderer::Init();

        // Initialize sub views
        InitMappingView();
        InitGlobalView();
        InitCamCalibView();

        m_MappingView.SetSize(600, 442);

        auto pt = GOPoint::Add(0, 0, 0, 5.0f);
        pt->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        // GOLine::Add(glm::vec3(0,0,0), glm::vec3(0,0,10), 10.0f);
        
        cout << "--------------------" << endl;
        auto myCylinder = GOCylinder::Add(glm::vec3(50,10,0), glm::vec3(50,0,10), 10.0f);
        myCylinder->SetColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        cout << "--------------------" << endl;
        // auto circle = GOCircle::Add(glm::vec3(0, 5, 0), 10.0f);
        // circle->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        // std::vector<glm::vec3> vertices = {
        //     glm::vec3(0.0f, 0.0f, 10.0f),
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(0.0f, 10.0f, 0.0f),
        //     glm::vec3(10.0f, 0.0f, 0.0f),
        // };
        // std::vector<glm::vec4> colors = {
        //     glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        //     glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
        //     glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        //     glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
        // };

        // m_TestGLObject = std::make_shared<GLPointObject>(vertices, colors, 3.0f);
        // glBindVertexArray(m_VAO);
        // m_TestGLObject = glCreatePoints(vertices, colors, 3);
        // cout << "m_TestGLObject: " << m_TestGLObject.vertexBuf << endl;

    }

    void Renderer::InitProjMatrix(){
        // Calculate Perspective Projection Matrix based on camera intrinsic parameters
        // Reference: https://strawlab.org/2011/11/05/augmented-reality-with-OpenGL/
        cv::Mat cameraMatrix = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetCameraMatrix();
        float camW = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetWidth();
        float camH = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetHeight();
        float x0 = 0, y0 = 0,zF = 100.0f, zN =0.01f;
        float fovX = cameraMatrix.at<float>(0,0);
        float fovY = cameraMatrix.at<float>(1,1);
        float cX = cameraMatrix.at<float>(0,2);
        float cY = cameraMatrix.at<float>(1,2);
        float perspectiveProjMatrixData[16] = {
                2 * fovX / camW,    0, ( camW - 2 * cX + 2 * x0) / camW,                         0,
                0,    2 * fovY / camH, (-camH + 2 * cY + 2 * y0) / camH,                         0,
                0,                  0,             (-zF - zN)/(zF - zN),  -2 * zF * zN / (zF - zN),
                0,                  0,                               -1,                         0
        };
        glm::mat4 perspectiveProjMatrix = glm::transpose(glm::make_mat4(perspectiveProjMatrixData));

        // opencv and opengl has different direction on y and z axis
        glm::mat4 scalarMatrix(1.0f);
        scalarMatrix[1][1] = -1;
        scalarMatrix[2][2] = -1;

        m_ProjMatrix = perspectiveProjMatrix * scalarMatrix;

        // Save variable for later use
        m_CamW = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetWidth();
        m_CamH = AIAC_APP.GetLayer<LayerCamera>()->MainCamera.GetHeight();
    }


    void Renderer::InitGlobalView()
    {
        m_GlobalView.Init(400, 300);

        // build camera visualization object, which is a pyramid
        const float CAMERA_SIZE_W = 1.6, CAMERA_SIZE_H = 1.2;
        float bW = CAMERA_SIZE_W / 2, bH = CAMERA_SIZE_H / 2, h = 0.5f;
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back( bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back(-bW,  bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back(-bW, -bH, 0);
        m_CamVisualizationEdges.emplace_back(  0,   0,-h);
        m_CamVisualizationEdges.emplace_back( bW, -bH, 0);

        m_GlobalProjMatrix = glm::perspective(
                glm::radians(35.0f),
                float(m_GlobalView.GetW()) / float(m_GlobalView.GetH()), 0.01f, 100.0f
        );

        m_GlobalCamMatrix = glm::lookAt(
                glm::vec3(20, 20, 20),   // the position of your camera, in world space
                DigitalModel.GetBboxCenter(),   // where you want to look at, in world space
                glm::vec3(0, 1, 0)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
        );

        auto testLookAt4TTool = glm::lookAt(
                glm::vec3(0, 0, 0),   // the position of your camera, in world space
                glm::vec3(0, 0, 1),   // where you want to look at, in world space
                glm::vec3(0, 1, 0)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
        );
    }

    void Renderer::ReloadMeshes()
    {
        auto pointCloudMapPath = AIAC::Config::Get<string>(AIAC::Config::SEC_RENDERER, AIAC::Config::PCD_MAP_PATH, "assets/tslam/examplePointCloud.ply");
        auto digitalModelPath = AIAC::Config::Get<string>(AIAC::Config::SEC_RENDERER, AIAC::Config::DIGITAL_MODEL_PATH, "assets/tslam/example3dModel.ply");

        PointCloudMap = Mesh(pointCloudMapPath);
        DigitalModel = Mesh(digitalModelPath);

        std::vector<std::string> meshPaths = AIAC::Config::GetVector<string>(AIAC::Config::SEC_RENDERER, AIAC::Config::MESH_PATHS, {});
        for(auto path : meshPaths) {
            Meshes.emplace_back(path);
        }
    }

    void Renderer::OnRender()
    {
        // During mapping, an overlay panel is opened, so we only render things on it
        // and stop updating the main scene.
        // TODO: mapping has some problem when calib file is switched (with slam map)
        if(AIAC_APP.GetLayer<LayerSlam>()->IsMapping()) {
            RenderGlobalView();
            RenderMappingView();
            return;
        }

        if(AIAC_APP.GetLayer<LayerCameraCalib>()->IsCalibrating()) {
            RenderCamCalibView();
            return;
        }

        // Default, render the main scene
        glBindVertexArray(m_VAO);
        glUseProgram(m_BasicShaderProgram);
        
        RenderMainView();
        RenderGlobalView();
    }

    void Renderer::SetGlobalViewSize(float w, float h) {
        m_GlobalView.SetSize(w, h);
        m_GlobalProjMatrix = glm::perspective(
                glm::radians(50.0f),
                w / h, 0.1f,300.0f
        );
    }

    void Renderer::UpdateGlobalViewCameraRotation(double diffX, double diffY){
        auto t1 = glm::translate(glm::mat4(1),-DigitalModel.BoundingBoxCenter);
        auto rx = glm::rotate(glm::mat4(1), float(-diffX / 100), glm::vec3(0,1,0));
        auto ry = glm::rotate(glm::mat4(1), float(-diffY / 100), glm::vec3(1,0,0));
        auto t2 = glm::translate(glm::mat4(1), DigitalModel.BoundingBoxCenter);
        m_GlobalCamMatrix = m_GlobalCamMatrix * t2 * rx * ry * t1;
    }

    void Renderer::UpdateGlobalViewCameraTranslation(double diffX, double diffY){
        m_GlobalCamMatrix[3][0] += float(diffX) / 10;
        m_GlobalCamMatrix[3][1] -= float(diffY) / 10;
    }

    void Renderer::UpdateGlobalViewCameraScale(double diff) {
        m_GlobalCamMatrix[3][2] += float(diff) / 10;
    }

    void Renderer::RenderGlobalView() {
        glBindVertexArray(m_VAO);
        glUseProgram(m_BasicShaderProgram);

        m_GlobalView.Activate();
        glBindVertexArray(m_VAO);
        glUseProgram(m_BasicShaderProgram);

        glDisable(GL_DEPTH_TEST);

        // visualize map
        glm::mat4 finalPoseMatrix = m_GlobalProjMatrix * m_GlobalCamMatrix;
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        // if(ShowPointCloudMap){
        //     PointCloudMap.DrawVertices(m_PointCloudMapColor, 1);
        // }
        if(ShowDigitalModel){
            // DigitalModel.DrawBoundingBoxEdges(m_DigitalModelBoundingBoxColor);
            // DigitalModel.DrawFaces(m_DigitalModelFaceColor);
        }

        // DrawSlamMap(AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap(), glm::vec4(1, 0, 0, 1));

        // visualize camera
        // auto camPoseInv = AIAC_APP.GetLayer<LayerSlam>()->GetInvCamPoseGlm(); // camera pose in world space
        // glm::mat4 cameraSpaceMVP = m_GlobalProjMatrix * m_GlobalCamMatrix * camPoseInv;
        // glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &cameraSpaceMVP[0][0]);
        // // glDrawLines3d(m_CamVisualizationEdges, glm::vec4(0, 0, 1, 1));
        // glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        // Draw All objects
        // DrawAllGOs(finalPoseMatrix);

        // Bind back to the main framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer::RenderMappingView() {
        glBindVertexArray(m_VAO);
        m_MappingView.Activate();

        RenderCameraFrame(600, 442);

        // visualize map
        glm::mat4 finalPoseMatrix = m_ProjMatrix * AIAC_APP.GetLayer<LayerSlam>()->GetCamPoseGlm();
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        DrawSlamMap(AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap(), glm::vec4(1, 0, 0, 1), 1.5);

        // Bind back to the main framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer::RenderCamCalibView() {
        m_CamCalibView.Activate();

        RenderCameraFrame(600, 442, true);

        // Bind back to the main framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer::RenderMainView() {
        glBindVertexArray(m_VAO);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderCameraFrame(AIAC_APP.GetWindow()->GetDisplayW(), AIAC_APP.GetWindow()->GetDisplayH());

        // finalPoseMatrix is the perspective projected pose of the current camera detected by SLAM
        glm::mat4 finalPoseMatrix = m_ProjMatrix * AIAC_APP.GetLayer<LayerSlam>()->GetCamPoseGlm();
        glUniformMatrix4fv(m_MatrixId, 1, GL_FALSE, &finalPoseMatrix[0][0]);

        // Draw the essential objects: map, point cloud map and digital model !
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glm::vec4 edgeColor;
        if(AIAC_APP.GetLayer<LayerSlam>()->IsTracked()) {
            if(ShowPointCloudMap){
                PointCloudMap.DrawVertices(m_PointCloudMapColor, 1);
            }
            if(ShowDigitalModel){
                DigitalModel.DrawBoundingBoxEdges(m_DigitalModelBoundingBoxColor);
                DigitalModel.DrawFaces(m_DigitalModelFaceColor);
            }
            for (auto& mesh : Meshes) {
                mesh.DrawEdges(m_DefaultEdgeColor);
            }
            // Draw All objects
            DrawAllGOs(finalPoseMatrix);
            DrawSlamMap(AIAC_APP.GetLayer<LayerSlam>()->Slam.getMap(), glm::vec4(1, 0, 0, 1));
        }
        // FIXME: for debug, get rid next line
        DrawAllGOs(finalPoseMatrix);
    }

    void Renderer::RenderCameraFrame(int w, int h, bool useRawFrame) {
        if ( w <= 0 || h <= 0 ){
            stringstream ss;
            ss << "Renderer::RenderCameraFrame: invalid size: (" << w << "," << h << ")";
            throw std::runtime_error(ss.str());
        }

        GLuint frameGlTextureObj;
        cv::Size frameSize;
        if(useRawFrame){
            frameGlTextureObj = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawCurrentFrame().GetGlTextureObj();
            frameSize.height = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawHeight();
            frameSize.width = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetRawWidth();
        } else {
            frameGlTextureObj = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetCurrentFrame().GetGlTextureObj();
            frameSize.height = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetHeight();
            frameSize.width = AIAC_APP.GetLayer<AIAC::LayerCamera>()->MainCamera.GetWidth();
        }

        GLuint readFboIdFrame = 0;
        glGenFramebuffers(1, &readFboIdFrame);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboIdFrame);
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, frameGlTextureObj, 0);

        glBlitFramebuffer(0, 0, frameSize.width, frameSize.height,
                          0, 0, w, h,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glDeleteFramebuffers(1, &readFboIdFrame);

        glViewport(0,0,w,h); // Renderer on the whole framebuffer, complete from the lower left corner to the upper right
    }
}