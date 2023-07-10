#pragma once

#include "AIAC/GOSys/GO.h"
#include "AIAC/GOSys/GOPrimitive.h"

#include <glm/glm.hpp>

namespace AIAC
{
    /// @section ACIT info ////////////////////////////////////////////////////////////////////////////
    /// @brief All the possible types of the toolheads in AC
    enum class ACToolHeadType
    {
        DRILLBIT,
        CIRCULARSAW,
        SABERSAW,
        CHAINSAW
    };

    /// @brief All the possible states of the toolheads in AC
    /**
        @brief Struct holding the data of the drillbit toolhead from .acit

        @param Name: name of the toolhead
        @param Toolbase: position of the base of the toolhead
        @param Tooltip: position of the tip of the toolhead
        @param Eattip: position of the tip of the toolhead eating the material
        @param Chucktip: position of the end of the drill chuck
        @param Radius: radius of the drillbit
    */
    struct DrillBitData
    {
        std::string Name;
        glm::vec3 Toolbase;
        glm::vec3 Tooltip;
        glm::vec3 Eattip;
        glm::vec3 Chucktip;
        float Radius;
    };
    /**
        @brief Structs holding the data of the drillbit toolhead from .acit

        @param Name: name of the toolhead
        @param Center: the center of the circle defining the circular blade
        @param NormalStart: start of the normal of the blade plane
        @param NormalEnd: end of the normal of the blade plane
        @param Radius: radius of the circular blade
    */
    struct CircularSawData
    {
        std::string Name;
        glm::vec3 Center;
        glm::vec3 NormalStart;
        glm::vec3 NormalEnd;
        float Radius;
    };
    /**
        @brief Structs holding the data of the chainsaw toolhead from .acit

        @param Name: name of the toolhead
        @param Chainbase: point start of the basetool
        @param Chainmid: point in the middle of the chain
        @param Chainend: point end of the chain before the round tip
        @param NormalStart: start of the normal of the blade plane
        @param NormalEnd: end of the normal of the blade plane
        @param Width: width of the chain
    */
    struct ChainSawData
    {
        glm::vec3 Chainbase;
        glm::vec3 Chainmid;
        glm::vec3 Chainend;
        glm::vec3 NormalStart;
        glm::vec3 NormalEnd;
        float Width;
    };
    /**
        @brief Struct holding the data of the drillbit toolhead from .acit

        @param Name: name of the toolhead
        @param Toolbase: position of the base of the toolhead
        @param Tooltip: position of the tip of the toolhead
        @param NormalStart: start of the normal of the blade plane
        @param NormalEnd: end of the normal of the blade plane
    */
    struct SaberSawData
    {
        std::string Name;
        glm::vec3 Toolbase;
        glm::vec3 Tooltip;
        glm::vec3 NormalStart;
        glm::vec3 NormalEnd;
    };

    /// @brief Class holding and parse the information from the .acit file of the toolhead
    class ToolHeadData
    {
        public:
            ToolHeadData() = default;
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
            /// @brief Retrieve scaling factor
            float GetScaleF() const { return m_ScaleF; }
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Type; }
            /// @brief Retrieve the name of the toolhead
            std::string GetName() const { return m_Name; }
            /// @brief Retrive the correct data type according to the type of tool of ToolHeadData
            template<typename T>
            T GetData() const
            {
                switch (m_Type)
                {
                    case ACToolHeadType::DRILLBIT:
                        return m_DrillBitD;
                        break;
                    case ACToolHeadType::CIRCULARSAW:
                        return m_CircularSawD;
                        break;
                    case ACToolHeadType::CHAINSAW:
                        return m_ChainSawD;
                        break;
                    case ACToolHeadType::SABERSAW:
                        return m_SaberSawD;
                        break;
                    default:
                        break;
                }
            }

        private:
            /// @brief Scaling factor from meters to AC scale
            float m_ScaleF = 50.0f;

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
            ACInfoToolhead(std::string acitPath, std::string meshObjPath, int id);

        public: __always_inline
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Data.GetType(); }
            /// @brief Get the name of the toolhead
            std::string GetName() const { return m_Data.GetName(); }
            /// @brief Get the id of the toolhead
            inline int GetId() const { return m_ID; }

        public:
            /// @brief From the parse data acit, create the corresponding geometries (e.g. GOPoint for tooltip, toolbase, etc)
            void AddGOsInfo(ToolHeadData& data);
            void AddGOsInfoDrillBit(ToolHeadData& data);
            void AddGOsInfoCircularSaw(ToolHeadData& data);
            void AddGOsInfoChainSaw(ToolHeadData& data);
            void AddGOsInfoSaberSaw(ToolHeadData& data);
            /// @brief From the parsed acit geometries, add widgets made by GOs (e.g. text, arrows, etc)
            void AddGOsWidget(ToolHeadData& data);
            void AddGOsWidgetDrillBit(ToolHeadData& data);
            void AddGOsWidgetCircularSaw(ToolHeadData& data);
            void AddGOsWidgetChainSaw(ToolHeadData& data);
            void AddGOsWidgetSaberSaw(ToolHeadData& data);

        public:
            /**
             * @brief Set the visibility of the geometries and widgets of the toolhead
             * 
             * @param visibleWidget: visibility of the widgets
             * @param visibleInfo: visibility of the geometries
             */
            void SetVisibility(bool visibleWidget, bool visibleInfo = false);

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
            /// @brief copy the original transform of the GO widgets
            void CopyGOsWidgetOriginal();

        public: __always_inline
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
            /// @brief the geometries the create the widget UI of the toolhead
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesWidget;
            /// @brief the original geometries of GOWidgets at loading time
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesWidgetOriginal;
    };
}