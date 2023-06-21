#pragma once

#include "AIAC/Layer.h"
#include "AIAC/Image.h"
#include "AIAC/Camera.h"

namespace AIAC
{
    class LayerCamera : public AIAC::Layer
    {
    public:
        LayerCamera() = default;
        virtual ~LayerCamera() = default;

        virtual void OnAttach() override;
        virtual void OnFrameStart() override;

        inline std::string GetCurrentDevice() const { return AvailableDevices[m_CurrentDeviceIndex]; }
        inline int GetCurrentDeviceIndex() const { return m_CurrentDeviceIndex; }
        void SetCurrentDevice(std::string path);
        void SetCurrentDeviceIndex(int index);

        /**
         * @brief Update the list of available devices
         *
         * @return true if the list contains >= 1 device
         * @return false if the list has no devices
         */
        bool UpdateAvailableDevices();

    public:
        std::vector<std::string> AvailableDevices;
        AIAC::Camera MainCamera;

    private:
        int m_CurrentDeviceIndex = 0;
    };
}