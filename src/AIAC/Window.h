#pragma once

#include "AIAC/GlHeader.h"
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

        void OnUpdate();
        void OnBufferSwap();
        void Shutdown();

        bool IsOpen();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        void SetVSync(bool enabled);
        inline bool IsVSync() const { return m_Data.VSync; }

        inline GLFWwindow* GetGLFWWindow() { return m_GLFWWindow; }
        inline const char* GetGlslVersion() { return m_GlslVersion; }

        inline int GetDisplayW() { return m_DisplayW; }
        inline int GetDisplayH() { return m_DisplayH; }

    private:
        void Init(const WindowProps& props);

    private:
        AIAC::TouchMonitor m_TouchMonitor;

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
        } m_Data;

        int m_DisplayW, m_DisplayH;
    };
}