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
#ifdef HEADLESS_TEST
        MainCamera.Open(0);
#else
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
#endif
    }

    bool LayerCamera::UpdateAvailableDevices(){
#ifdef HEADLESS_TEST
        return true;
#endif
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