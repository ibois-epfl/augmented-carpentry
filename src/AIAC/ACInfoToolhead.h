#pragma once

#include <type_traits>

#include "AIAC/GOSys/GO.h"
#include "AIAC/GOSys/GOPrimitive.h"
#include "Config.h"

#include <glm/glm.hpp>

namespace AIAC
{
    /// @section Structs holding the data of the toolheads from .acit and the corresponding GOs
    /// @brief All the possible types of the toolheads in AC
    enum class ACToolHeadType
    {
        DRILLBIT,
        CIRCULARSAW,
        SABERSAW,
        CHAINSAW
    };

    struct DrillBitData
    {
        /// @brief name of the toolhead
        std::string NameACIT;
        /// @brief radius of the drillbit
        float RadiusACIT;

        /// @brief original position of the base of the toolhead
        glm::vec3 ToolbaseACIT;
        /// @brief original position of the tip of the toolhead
        glm::vec3 TooltipACIT;
        /// @brief original position of the tip of the toolhead eating the material
        glm::vec3 EattipACIT;
        /// @brief original position of the end of the drill chuck
        glm::vec3 ChucktipACIT;
        /// @brief GOPoints equivalent
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
        /// @brief name of the toolhead
        std::string NameACIT;
        /// @brief radius of the circular blade
        float RadiusACIT;
        /// @brief the overhaul thickness of the blade
        float ThicknessACIT;
        /// @brief the overhang width of the teeth of the blade from one side
        float OverhangACIT;

        /// @brief center of the circle defining the circular blade
        glm::vec3 CenterACIT;
        /// @brief start of the normal of the blade plane
        glm::vec3 NormStartACIT;
        /// @brief end of the normal of the blade plane
        glm::vec3 NormEndACIT;
        /// @brief GOPoints equivalent
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
        /// @brief name of the toolhead
        std::string NameACIT;
        /// @brief width of the chain
        float WidthACIT;
        /// @brief the overhaul thickness of the blade
        float ThicknessACIT;
        /// @brief the overhang width of the teeth of the blade from one side
        float OverhangACIT;

        /// @brief point start of the basetool
        glm::vec3 ChainBaseACIT;
        /// @brief point in the middle of the chain
        glm::vec3 ChainMidACIT;
        /// @brief point end of the chain before the round tip
        glm::vec3 ChainNormEndACIT;
        /// @brief start of the normal of the plateau plane
        glm::vec3 NormStartACIT;
        /// @brief end of the normal of the plateau plane
        glm::vec3 NormEndACIT;
        /// @brief GOPoints equivalent
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
        /// @brief name of the toolhead
        std::string NameACIT;

        /// @brief position of the base of the toolhead
        glm::vec3 ToolbaseACIT;
        /// @brief position of the tip of the toolhead
        glm::vec3 TooltipACIT;
        /// @brief start of the normal of the blade plane
        glm::vec3 NormStartACIT;
        /// @brief end of the normal of the blade plane
        glm::vec3 NormEndACIT;
        /// @brief GOPoints equivalent
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

    /// @brief Class holding and parse and create data from the .acit file of the toolhead
    class ToolHeadData
    {
        public:
            ToolHeadData(){
                this->m_ScaleF = AIAC::Config::Get<float>(AIAC::Config::SEC_AIAC, AIAC::Config::SCALE_FACTOR, 1.0f);
            }
            ~ToolHeadData() = default;
        private:
            /**
                @brief Load the .acit file and parse the data into the correct struct member values
                @param path: path to the .acit file
            */
            void LoadACIT(std::string path);
            /**
                @brief Parse a string into a glm::vec3
                @param str: string to parse
                @return glm::vec3: the parsed vector
            */
            glm::vec3 ParseString2GlmVector(std::string str);

        private: __always_inline
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Type; }
            /// @brief Retrieve the type of the toolhead as a string
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
            /// @brief Retrieve the name of the toolhead
            std::string GetName() const { return m_Name; }
            /// @brief  Retrieve the data of the toolhead+
            /// @tparam T the type of the data to retrieve (DrillBitData, CircularSawData, ChainSawData, SaberSawData)
            /// @return the data of the toolhead struct
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

            /// @brief Retrieve scaling factor
            float GetScaleF() const { return m_ScaleF; }

        public: __always_inline ///< utils
            /// @brief convert to a string
            std::string ToString() const { return m_Name;}

        private:
            /// @brief Scaling factor from meters to AC scale
            float m_ScaleF = 0.0f;

            /// @brief Type of the toolhead
            ACToolHeadType m_Type;
            /// @brief Type of the toolhead
            std::string m_Name;

            /// @brief struct contains info from .acit data for drillbit
            DrillBitData m_DrillBitD;
            /// @brief struct contains info from .acit data for circularsaw
            CircularSawData m_CircularSawD;
            /// @brief struct contains info from .acit data for chainsaw
            ChainSawData m_ChainSawD;
            /// @brief struct contains info from .acit data for sabersaw
            SaberSawData m_SaberSawD;

            friend class ACInfoToolhead;
    };

    /// @brief the class holding the information of the toolhead (GOs, metadata, etc)
    class ACInfoToolhead
    {
        public:
            ACInfoToolhead() = default;
            ACInfoToolhead(std::string acitPath, std::string meshObjPath, int id);

        public: __always_inline
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Data.GetType(); }
            /// @brief Retrieve the type of the toolhead as a string
            std::string GetTypeString() const { return m_Data.GetTypeString();}
            /// @brief Get the name of the toolhead
            std::string GetName() const { return m_Data.GetName(); }
            /// @brief Get the id of the toolhead
            int GetId() const { return m_ID; }

            /// @brief access the data of the toolheads
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
            /// @brief From the parse data acit, create the corresponding geometries (e.g. GOPoint for tooltip, toolbase, etc)
            void AddGOsInfo(ToolHeadData& data);
            void AddGOsInfoDrillBit(ToolHeadData& data);
            void AddGOsInfoCircularSaw(ToolHeadData& data);
            void AddGOsInfoChainSaw(ToolHeadData& data);
            void AddGOsInfoSaberSaw(ToolHeadData& data);

        public:
            /// @brief Set the visibility of the geometries and widgets of the toolhead
            void SetVisibility(bool visible);

        public:
            /// @brief transform all the geometries, widgets and mesh contained in the ACInfoToolhead object
            void Transform(glm::mat4 transform);
            /// @brief transform a specific geometry
            void TransformGO(std::shared_ptr<GOPrimitive> goPtr,
                             std::shared_ptr<GOPrimitive> goOriginalPtr,
                             glm::mat4 transform);
            /// @brief rotate around local x axis of the toolhead 90 degrees to match the AC coordinate system with the TTool coordinate system
            /// Should only be called once at loading time
            void TransformSync();

            /// @brief copy the original transform of the GO infos
            void CopyGOsInfoOriginal();

        public: __always_inline
            /// @brief convert to a string byy getting the name
            std::string ToString() const { return m_Data.GetName(); }

        private:
            /// @brief the path to the acit file
            std::string m_ACITPath;
            /// @brief the path to the mesh file as obj
            std::string m_OBJPath;
            /// @brief the data loaded from the .acit
            ToolHeadData m_Data;
            /// @brief the id of the object given by its path index position in the config file
            int m_ID;

        private:
            /// @brief the geometries that defines the hole and used in the feedback layer
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesInfo;
            /// @brief the original geometries of GOinfos at loading time
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesInfoOriginal;
    };
}
