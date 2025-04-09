

# File ACInfoToolhead.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**ACInfoToolhead.h**](ACInfoToolhead_8h.md)

[Go to the documentation of this file](ACInfoToolhead_8h.md)


```C++
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

#include <type_traits>

#include "AIAC/GOSys/GO.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "Config.h"

#include <glm/glm.hpp>

namespace AIAC
{
    enum class ACToolHeadType
    {
        DRILLBIT,
        CIRCULARSAW,
        SABERSAW,
        CHAINSAW
    };

    struct DrillBitData
    {
        std::string NameACIT;
        float RadiusACIT;

        glm::vec3 ToolbaseACIT;
        glm::vec3 TooltipACIT;
        glm::vec3 EattipACIT;
        glm::vec3 ChucktipACIT;
        std::shared_ptr<GOPoint> ToolbaseGO;
        std::shared_ptr<GOPoint> TooltipGO;
        std::shared_ptr<GOPoint> EattipGO;
        std::shared_ptr<GOPoint> ChucktipGO;
    
        DrillBitData()
        {
            ToolbaseGO = std::make_shared<GOPoint>();
            TooltipGO = std::make_shared<GOPoint>();
            EattipGO = std::make_shared<GOPoint>();
            ChucktipGO = std::make_shared<GOPoint>();
        }
    };
    struct CircularSawData
    {
        std::string NameACIT;
        float RadiusACIT;
        float ThicknessACIT;
        float OverhangACIT;

        glm::vec3 CenterACIT;
        glm::vec3 NormStartACIT;
        glm::vec3 NormEndACIT;
        std::shared_ptr<GOPoint> CenterGO;
        std::shared_ptr<GOPoint> NormStartGO;
        std::shared_ptr<GOPoint> NormEndGO;

        CircularSawData()
        {
            CenterGO = std::make_shared<GOPoint>();
            NormStartGO = std::make_shared<GOPoint>();
            NormEndGO = std::make_shared<GOPoint>();
        }
    };
    struct ChainSawData
    {
        std::string NameACIT;
        float WidthACIT;
        float ThicknessACIT;
        float OverhangACIT;

        glm::vec3 ChainBaseACIT;
        glm::vec3 ChainMidACIT;
        glm::vec3 ChainNormEndACIT;
        glm::vec3 NormStartACIT;
        glm::vec3 NormEndACIT;
        std::shared_ptr<GOPoint> ChainBaseGO;
        std::shared_ptr<GOPoint> ChainMidGO;
        std::shared_ptr<GOPoint> ChainEndGO;
        std::shared_ptr<GOPoint> NormStartGO;
        std::shared_ptr<GOPoint> NormEndGO;

        ChainSawData()
        {
            ChainBaseGO = std::make_shared<GOPoint>();
            ChainMidGO = std::make_shared<GOPoint>();
            ChainEndGO = std::make_shared<GOPoint>();
            NormStartGO = std::make_shared<GOPoint>();
            NormEndGO = std::make_shared<GOPoint>();
        }
    };
    struct SaberSawData
    {
        std::string NameACIT;

        glm::vec3 ToolbaseACIT;
        glm::vec3 TooltipACIT;
        glm::vec3 NormStartACIT;
        glm::vec3 NormEndACIT;
        std::shared_ptr<GOPoint> ToolbaseGO;
        std::shared_ptr<GOPoint> TooltipGO;
        std::shared_ptr<GOPoint> NormStartGO;
        std::shared_ptr<GOPoint> NormEndGO;

        SaberSawData()
        {
            ToolbaseGO = std::make_shared<GOPoint>();
            TooltipGO = std::make_shared<GOPoint>();
            NormStartGO = std::make_shared<GOPoint>();
            NormEndGO = std::make_shared<GOPoint>();
        }
    };

    class ToolHeadData
    {
        public:
            ToolHeadData(){
                this->m_ScaleF = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
            }
            ~ToolHeadData() = default;
        private:
            void LoadACIT(std::string path);
            glm::vec3 ParseString2GlmVector(std::string str);

        private: __always_inline
            ACToolHeadType GetType() const { return m_Type; }
            std::string GetTypeString() const
            {
                if (this->GetType() == ACToolHeadType::DRILLBIT)
                    return "DRILLBIT";
                else if (this->GetType() == ACToolHeadType::CIRCULARSAW)
                    return "CIRCULARSAW";
                else if (this->GetType() == ACToolHeadType::CHAINSAW)
                    return "CHAINSAW";
                else if (this->GetType() == ACToolHeadType::SABERSAW)
                    return "SABERSAW";
                else
                    throw std::out_of_range("Tool head type unknown");
            }
            std::string GetName() const { return m_Name; }
            template <typename T>
            T GetData() const
            {
                if constexpr (std::is_same_v<T, DrillBitData>)
                    return m_DrillBitD;
                else if constexpr (std::is_same_v<T, CircularSawData>)
                    return m_CircularSawD;
                else if constexpr (std::is_same_v<T, ChainSawData>)
                    return m_ChainSawD;
                else if constexpr (std::is_same_v<T, SaberSawData>)
                    return m_SaberSawD;
            }

            float GetScaleF() const { return m_ScaleF; }

        public: __always_inline 
            std::string ToString() const { return m_Name;}

        private:
            float m_ScaleF = 0.0f;

            ACToolHeadType m_Type;
            std::string m_Name;

            DrillBitData m_DrillBitD;
            CircularSawData m_CircularSawD;
            ChainSawData m_ChainSawD;
            SaberSawData m_SaberSawD;

            friend class ACInfoToolhead;
    };

    class ACInfoToolhead
    {
        public:
            ACInfoToolhead() = default;
            ACInfoToolhead(std::string acitPath, std::string meshObjPath, int id);

        public: __always_inline
            ACToolHeadType GetType() const { return m_Data.GetType(); }
            std::string GetTypeString() const { return m_Data.GetTypeString();}
            std::string GetName() const { return m_Data.GetName(); }
            int GetId() const { return m_ID; }

            template <typename T>
            T GetData() const
            {
                if constexpr (std::is_same_v<T, DrillBitData>)
                    return m_Data.GetData<DrillBitData>();
                else if constexpr (std::is_same_v<T, CircularSawData>)
                    return m_Data.GetData<CircularSawData>();
                else if constexpr (std::is_same_v<T, ChainSawData>)
                    return m_Data.GetData<ChainSawData>();
                else if constexpr (std::is_same_v<T, SaberSawData>)
                    return m_Data.GetData<SaberSawData>();
            }
            
        public:
            void AddGOsInfo(ToolHeadData& data);
            void AddGOsInfoDrillBit(ToolHeadData& data);
            void AddGOsInfoCircularSaw(ToolHeadData& data);
            void AddGOsInfoChainSaw(ToolHeadData& data);
            void AddGOsInfoSaberSaw(ToolHeadData& data);

        public:
            void SetVisibility(bool visible);

        public:
            void Transform(glm::mat4 transform);
            void TransformGO(std::shared_ptr<GOPrimitive> goPtr,
                             std::shared_ptr<GOPrimitive> goOriginalPtr,
                             glm::mat4 transform);
            void TransformSync();

            void CopyGOsInfoOriginal();

        public: __always_inline
            std::string ToString() const { return m_Data.GetName(); }

        private:
            std::string m_ACITPath;
            std::string m_OBJPath;
            ToolHeadData m_Data;
            int m_ID;

        private:
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesInfo;
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesInfoOriginal;
    };
}
```


