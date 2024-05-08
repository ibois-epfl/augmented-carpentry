#pragma once

#include "Layer.h"

namespace AIAC
{
    class LayerRecorder : public AIAC::Layer
    {
    public:
        LayerRecorder() = default;
        virtual ~LayerRecorder() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

    public:
        /**
         * @brief Start recording the log to a file
         *
         * @param logFilename The filename of the log file
         */
        void StartRecording(std::string logFilename);

        /**
         * @brief Stop recording the log to a file
         */
        void StopRecording();

        /**
         * @brief Check if the recorder is on
         *
         * @return true if it's recording, false otherwise
         */
        bool IsRecording() const { return m_IsRecording; }

    private:
        bool m_IsRecording = false;
        std::string m_LogFilename;
    };
}
