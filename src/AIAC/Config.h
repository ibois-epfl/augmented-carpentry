#pragma once
#include <string>

#include "AIAC/Log.h"
#include "AIAC/Assert.h"

#include "utils/Ini.h"

namespace AIAC{
class Config
{
public:
    inline static const std::string SEC_AIAC = "AIAC";
    inline static const std::string CAM_ID = "CamID";
    inline static const std::string CAM_PARAMS_FILE = "CamParamsFile";
    inline static const std::string AC_INFO_MODEL = "ACInfoModel";
    inline static const std::string SCANNED_MODEL = "ScannedModel";
    inline static const std::string ALIGN_OFFSET = "AlignOffset";
    inline static const std::string ALIGN_ROTATION = "AlignRotation";
    inline static const std::string ALIGN_FLIP = "AlignFlip";
    inline static const std::string SCALE_FACTOR = "ScaleFactor";

    inline static const std::string SEC_TSLAM = "TSlam";
    inline static const std::string MAP_FILE = "MapFile";
    inline static const std::string VocFile = "VocFile";
    inline static const std::string RECONSTRUCT_CONFIG_DEFAULT_FILE = "ReconstructConfigDefaultFile";
    inline static const std::string SAVE_DIR_MAPS = "SaveDirMaps";

    inline static const std::string SEC_TTOOL = "TTool";
    inline static const std::string CONFIG_FILE = "ConfigFile";
    inline static const std::string DATASET_DIR = "DatasetDir";
    inline static const std::string TTOOL_ROOT_PATH = "TToolRootPath";
    inline static const std::string CACHED_TOOLHEAD = "CachedToolhead";

    inline static const std::string SEC_RENDERER = "Renderer";
    inline static const std::string PCD_MAP_PATH = "PointCloudMapPath";
    inline static const std::string DIGITAL_MODEL_PATH = "DigitalModelPath";
    inline static const std::string MESH_PATHS = "MeshPaths";

    inline static const std::string SEC_UTILS = "Utils";
    inline static const std::string UTILS_PATH = "UtilsPath";

public:
    Config(std::string filename, bool updateFile=true):
        m_Filename(filename),
        m_UpdateFile(updateFile)
    {
        AIAC_ASSERT(!s_Instance, "Config already exists!");
        s_Instance = this;

        m_IniReader = inih::INIReader(m_Filename);
    }

    template <typename T>
    inline static T Get(const std::string& section, const std::string& name)
    {
        AIAC_ASSERT(s_Instance, "Config not initialized!");
        try {
            return s_Instance->m_IniReader.Get<T>(section, name);
        } catch (std::runtime_error& e) {
            AIAC_ERROR("Failed to get value from config: {0}", e.what());
            return nullptr;
        }
    }

    template <typename T>
    inline static T Get(const std::string& section, const std::string& name, T&& default_v)
    {
        AIAC_ASSERT(s_Instance, "Config not initialized!");
        try {
            return s_Instance->m_IniReader.Get<T>(section, name);
        } catch (std::runtime_error& e) {
            s_Instance->m_IniReader.InsertEntry(section, name, default_v);
            if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
            return default_v;
        }
    }

    template <typename T>
    inline static std::vector<T> GetVector(const std::string& section,
                             const std::string& name,
                             const std::vector<T>& default_v)
    {
        AIAC_ASSERT(s_Instance, "Config not initialized!");
        try {
            return s_Instance->m_IniReader.GetVector<T>(section, name);
        } catch (std::runtime_error& e) {
            s_Instance->m_IniReader.InsertEntry(section, name, default_v);
            if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
            return default_v;
        }
    }

    template <typename T = std::string>
    inline static void InsertEntry(const std::string& section, const std::string& name, const T& v)
    {
        AIAC_ASSERT(s_Instance != NULL, "Config not initialized!");
        AIAC_INFO("Insert config value: [{}] {} = {}", section, name, v);
        s_Instance->m_IniReader.InsertEntry(section, name, v);
        if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
    };

    template <typename T = std::string>
    inline static void InsertEntry(const std::string& section, const std::string& name, const std::vector<T>& vs)
    {
        AIAC_ASSERT(s_Instance != NULL, "Config not initialized!");
        AIAC_INFO("Insert config value: [{}] {} = {}...", section, name, vs[0]);
        s_Instance->m_IniReader.InsertEntry(section, name, vs);
        if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
    };

    template <typename T = std::string>
    inline static void UpdateEntry(const std::string& section, const std::string& name, const T& v)
    {
        AIAC_ASSERT(s_Instance != NULL, "Config not initialized!");
        AIAC_INFO("Update config value: [{}] {} = {}", section, name, v);
        s_Instance->m_IniReader.UpdateEntry(section, name, v);
        if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
    }

    template <typename T = std::string>
    inline static void UpdateEntry(const std::string& section, const std::string& name,
                     const std::vector<T>& vs)
    {
        AIAC_ASSERT(s_Instance, "Config not initialized!");
        AIAC_INFO("Update config value: [{}] {} = {}...", section, name, vs[0]);
        s_Instance->m_IniReader.UpdateEntry(section, name, vs);
        if(s_Instance->m_UpdateFile) s_Instance->WriteToFile();
    };

    inline static void WriteToFile(std::string writeFilename="")
    {
        if(writeFilename.empty()) writeFilename = s_Instance->m_Filename;
        inih::INIWriter::write(writeFilename, s_Instance->m_IniReader);
    };

private:
    inih::INIReader m_IniReader;
    std::string m_Filename;
    bool m_UpdateFile = true;

    static Config* s_Instance;
};
}