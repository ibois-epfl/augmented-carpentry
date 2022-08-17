#pragma once


namespace AIAC
{
    class Monitor
    {
    public:
        Monitor();
        virtual ~Monitor() = default;

        void Init();

        inline std::string ImportMonitorName();
        inline std::string ImportMonitorLinkType();
        inline std::string ImportMonitorResolution();
        void ParseResolution2Int32_t()
            {
                m_ResW = std::stoi(m_Resolution.substr(0, m_Resolution.find('x')));
                m_ResH = std::stoi(m_Resolution.substr(m_Resolution.find('x') + 1));
            }
        
        void ImportParamFromConfig();

        bool FindMonitorID();

        bool Check4MonitorNbr();
        bool Check4MonitorRes();

        bool MapMonitor();

        inline static Monitor& GetInstance() { return *s_Instance; }
        inline bool IsTouch() const { return m_IsTouch; }
        inline std::string GetMonitorName() const { return m_MonitorName; }
        inline std::string GetMonitorLinkType() const { return m_MonitorLinkType; }
        inline std::string GetResolution() const { return m_Resolution; }
        inline int32_t GetResWidth() const { return m_ResW; }
        inline int32_t GetResHeight() const { return m_ResH; }
        inline int32_t GetMonitorID() const { return m_TouchMonitorId; }

    private:
        static Monitor* s_Instance;

        bool m_IsTouch;

        std::string m_MonitorName;
        std::string m_MonitorLinkType;
        std::string m_Resolution;
        int32_t m_ResW, m_ResH;

        int32_t m_TouchMonitorId = -1;

        char m_Buffer[1024];
        FILE* m_Fpipe;
    };
}