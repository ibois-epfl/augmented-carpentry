#pragma once

#include <fstream>
#include "Layer.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace AIAC
{
    class LayerLogRecorder : public AIAC::Layer
    {
    public:
        LayerLogRecorder() = default;
        virtual ~LayerLogRecorder() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    public:
        /**
         * @brief Start recording the log to a file
         *
         * @param logRootFolderPath The filename of the log file
         */
        void StartRecording(std::string logRootFolderPath = "");

        /**
         * @brief Stop recording the log to a file
         */
        void StopRecording();

        /**
         * @brief Pause recording
         */
        void PauseRecording();

        /**
         * @brief Pause recording
         */
        void ResumeRecording();

        /**
         * @brief the recorder is on
         *
         * @return true if it's recording, false otherwise
         */
        bool IsRecording() const { return m_IsRecording; }

        /**
         * @brief the recoder is paused
         */
         bool IsPaused() const { return m_IsPaused; }
    private:
        /**
         * @brief log header information to the file
         */
        void LogHeader();

        /**
         * @brief Log the SLAM status of the current frame
         */
        void LogSlamStatus();

        /**
         * @brief Log the TTool status & pose of the current frame
         */
        void LogTToolHead();

        /**
         * @brief Log the TTool pose
         */
        void LogTToolPose();

        /**
         * @brief Initialize the variables storing TTool's state
         */
        void InitTToolStatus();

        /**
         * @brief Log TTool's transformation
         *
         * @param status The status of the TTool
         */
        void LogTToolTransformation(const std::string& status);

        /**
         * @brief Log the ACInfoModel status of the current frame
         */
        void LogACIM();

        /**
         * @brief Initialize the variables storing ACIM's state
         */
        void InitACIMStatus();

        /**
         * @brief Log ACIM's transformation
         */
        void LogACIMTransformation();


    private:
        bool m_IsRecording = false;
        bool m_IsPaused = false;
        std::string m_LogFolderPath;
        std::string m_LogFilePath;
        std::ofstream m_LogFile;
        int m_FrameCount = 0;

        // variables for TTool
        std::set<std::string> m_TToolStatusToLog = {
            "PoseInput",
            "Tracking",
        };
        std::string m_TToolPreviousToolheadName;

        // variables for ACInfoModel
        std::string m_ACIMPreviousActivatedComponentID;
        bool m_IsActivatedComponentDone = false;
        double m_ACIMOffset = INFINITY;
        int m_ACIMRotation = INT_MAX;
        bool m_ACIMFlip = false;
        std::unordered_map<std::string, bool> m_ACIMComponentStatus;
    };
}