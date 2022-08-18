#pragma once


namespace AIAC
{
    class MonitorConfig
    {
    public:
        MonitorConfig();
        virtual ~MonitorConfig() = default;

        inline std::string ImportMonitorConfigNameFromConfig();
        inline std::string ImportMonitorConfigLinkTypeFromConfig();
        inline std::string ImportMonitorConfigResolutionFromConfig();
        void ImportParamFromConfig();

        void ParseResolution2Int32_t()
            {
                m_ResW = std::stoi(m_Resolution.substr(0, m_Resolution.find('x')));
                m_ResH = std::stoi(m_Resolution.substr(m_Resolution.find('x') + 1));
            }

        bool FindMonitorConfigID();       // Linux-based only
        bool Check4MonitorConfigNbr();    // Linux-based only
        bool Check4MonitorConfigRes();    // Linux-based only
        bool MapMonitorConfig();          // Linux-based only

        inline static MonitorConfig& GetInstance() { return *s_Instance; }
        inline bool IsTouch() const { return m_IsTouch; }
        inline std::string GetMonitorConfigName() const { return m_MonitorConfigName; }
        inline std::string GetMonitorConfigLinkType() const { return m_MonitorConfigLinkType; }
        inline std::string GetResolution() const { return m_Resolution; }
        inline int32_t GetResWidth() const { return m_ResW; }
        inline int32_t GetResHeight() const { return m_ResH; }
        inline int32_t GetMonitorConfigID() const { return m_TouchMonitorConfigId; }
    
    private:
        void Init();

    private:
        static MonitorConfig* s_Instance;

        bool m_IsTouch;

        std::string m_MonitorConfigName;
        std::string m_MonitorConfigLinkType;
        std::string m_Resolution;
        int32_t m_ResW, m_ResH;

        int32_t m_TouchMonitorConfigId = -1;

        char m_Buffer[1024];
        FILE* m_Fpipe;
    };
}