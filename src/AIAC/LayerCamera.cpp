#include "aiacpch.h"

#include "AIAC/LayerCamera.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "utils/glob.h"

namespace AIAC
{
    void LayerCamera::OnAttach()
    {
        try
        {
            glob::glob glob("/dev/video*");
            while(glob){
                AvailableDevices.push_back(glob.current_match());
                glob.next();
            }
            sort(AvailableDevices.begin(), AvailableDevices.end());
            if (AvailableDevices.empty()) {
                AIAC_ERROR("No camera device found");
            } else {
                AIAC_INFO("Found {} camera devices", AvailableDevices.size());
                // open 0 for default
                MainCamera.Open(m_CurrentDeviceIndex);
            }
        }
        catch(const std::runtime_error& e)
        {
            AIAC_ERROR(e.what());
        }
    }

    void LayerCamera::OnFrameStart()
    {
        MainCamera.GetNextFrame();
    }

    void LayerCamera::SetCurrentDevice(std::string path) {
        auto it = std::find(AvailableDevices.begin(), AvailableDevices.end(), path);
        if (it != AvailableDevices.end()) {
            int prevDeviceIdx = m_CurrentDeviceIndex;
            m_CurrentDeviceIndex = std::distance(AvailableDevices.begin(), it);
            try {
                MainCamera.Open(m_CurrentDeviceIndex);
            } catch (const std::runtime_error& e) {
                m_CurrentDeviceIndex = prevDeviceIdx;
                MainCamera.Open(m_CurrentDeviceIndex);
                AIAC_ERROR(e.what() + std::string(" Revert to previous device"));
            }
        } else {
            AIAC_ERROR("Device {} not found", path);
        }
    }

    void LayerCamera::SetCurrentDeviceIndex(int index) {
        if (index >= 0 && index < AvailableDevices.size()) {
            m_CurrentDeviceIndex = index;
            MainCamera.Open(m_CurrentDeviceIndex);
        } else {
            AIAC_ERROR("Device index {} out of range", index);
        }
    }
}