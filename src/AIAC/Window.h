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
#pragma once

#include "GlHeader.h"
#include "AIAC/TouchMonitor.h"
namespace AIAC
{
    struct WindowProps
    {
        const char* Title;
        uint32_t Width;
        uint32_t Height;
        bool VSync;
        bool IsResizable;

        WindowProps(const char* title = "augmented_carpentry",
                    uint32_t width = 800,
                    uint32_t height = 480,
                    bool vSync = true,
                    bool isResizable = false)
            : Title(title), Width(width), Height(height), VSync(vSync), IsResizable(isResizable)
        {}
    };


    class Window
    {
    public:
        Window(const WindowProps& props);
        virtual ~Window();

        void Init();

        void OnUpdate();
        void OnBufferSwap();
        void Shutdown();
        void MakeCurrent();
        void ReleaseCurrent();

        bool IsOpen();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        void SetVSync(bool enabled);
        inline bool IsVSync() const { return m_Data.VSync; }

        inline GLFWwindow* GetGLFWWindow() { return m_GLFWWindow; }
        inline const char* GetGlslVersion() { return m_GlslVersion; }

        inline int GetDisplayW() { return m_DisplayW; }
        inline int GetDisplayH() { return m_DisplayH; }

//    private:
//        static void m_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
//        static void m_MouseMoveCallback(GLFWwindow* window, double x, double y);

    private:
        AIAC::TouchMonitor* m_TouchMonitor;

        GLFWwindow* m_GLFWWindow;
        const char* m_GlslVersion;
        bool m_IsWindowOpen;

        struct WindowData
        {
            const char* Title;
            uint32_t Width;
            uint32_t Height;
            bool VSync;
            bool IsResizable;
        } m_Data = {};

        int m_DisplayW, m_DisplayH;
    };
}