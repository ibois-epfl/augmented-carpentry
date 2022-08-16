#pragma once


namespace AIAC
{
    class Monitor
    {
    public:
        Monitor();
        virtual ~Monitor() = default;

        void Init();

        void ImportParamFromConfig();

        bool FindMonitorID();

        bool Check4MonitorNbr();
        bool Check4MonitorRes();

        bool MapMonitor();

        inline static Monitor& GetInstance() { return *s_Instance; }
        inline bool IsTouch() const { return m_IsTouch; }
        inline std::string GetMonitorName() const { return m_TouchMonitorName; }
        inline std::string GetMonitorLinkType() const { return m_TouchMonitorLinkType; }
        inline std::string GetResolution() const { return m_TouchResolution; }
        inline int32_t GetMonitorID() const { return m_TouchMonitorId; }

    private:
        static Monitor* s_Instance;

        bool m_IsTouch;

        std::string m_TouchMonitorName;
        std::string m_TouchMonitorLinkType;
        std::string m_TouchResolution;

        int32_t m_TouchMonitorId = -1;

        char m_Buffer[1024];
        FILE* m_Fpipe;
    };
}