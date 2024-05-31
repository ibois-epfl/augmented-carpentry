#include "aiacpch.h"

#include "AIAC/LayerCamera.h"
#include "AIAC/Log.h"
#include "AIAC/Application.h"
#include "AIAC/Config.h"
#include "utils/glob.h"

namespace AIAC
{
    void LayerCamera::OnAttach()
    {
        try
        {
            if(UpdateAvailableDevices()){
                m_CurrentDeviceIndex = AIAC::Config::Get<int>("AIAC", "CamID", 0);
                SetCurrentDeviceIndex(m_CurrentDeviceIndex);
            } else {
                throw std::runtime_error("No camera found, connect a camera");
            }
        }
        catch(const std::runtime_error& e)
        {
            AIAC_ERROR(e.what());
            AIAC::Application::GetInstance().Close();
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
                AIAC::Config::UpdateEntry("AIAC", "CamID", m_CurrentDeviceIndex);
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
        try {
            if (index >= 0 && index < AvailableDevices.size()) {
                MainCamera.Open(index);
                m_CurrentDeviceIndex = index;
            } else {
                AIAC_ERROR("Camera device index {} out of range (0~{})", index, AvailableDevices.size() - 1);
                MainCamera.Open(0);
                m_CurrentDeviceIndex = 0;
            }
            AIAC::Config::UpdateEntry("AIAC", "CamID", m_CurrentDeviceIndex);
        } catch (const std::runtime_error &e) {
            AIAC_ERROR(e.what());
        }
    }

    bool LayerCamera::UpdateAvailableDevices(){
        AvailableDevices.clear();
        glob::glob glob("/dev/video*");
        while(glob){
            AvailableDevices.push_back(glob.current_match());
            glob.next();
        }
        if(AvailableDevices.empty()){
            AIAC_ERROR("No camera device found");
            return false;
        }
        sort(AvailableDevices.begin(), AvailableDevices.end());
        return true;
    }
}