#pragma once

#include "AIAC/GOSys/GO.h"

#include <glm/glm.hpp>
/*
    the class hold the toolhead, it should:
    - (A) hold the geometric information of the toolhead with GoTypes
    - (A2) have the mesh of the toolhead for representation
    - (B) have state, type, property members and util functions linked to it
    - a transform/rotate/translate function to apply to all the GoTypes
*/

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
    /*
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
    /*
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
    /*
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
        std::string Name;
        glm::vec3 Chainbase;
        glm::vec3 Chainmid;
        glm::vec3 Chainend;
        glm::vec3 NormalStart;
        glm::vec3 NormalEnd;
        float Width;
    };
    /*
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
            /*
                @brief Load the .acit file and parse the data into the correct struct member values
                @param path: path to the .acit file
            */
            void LoadACIT(std::string path);
            /*
                @brief Parse a string into a glm::vec3
                @param str: string to parse
                @return glm::vec3: the parsed vector
            */
            glm::vec3 ParseString2GlmVector(std::string str);

        public: __always_inline
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Type; }
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
            /// @brief Name of the toolhead
            ACToolHeadType m_Type;
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

    /// @section ACIT Model ////////////////////////////////////////////////////////////////////////////
    class ACInfoToolhead
    {
        enum class ToolHeadState
        {
            IDLE,
            ACTIVE
        };

        public:
            ACInfoToolhead(std::string acitPath);

            void Init();

        public: __always_inline
            /// @brief Retrieve the type of the toolhead
            ACToolHeadType GetType() const { return m_Data.GetType(); }

        private:
            /// @brief the data loaded from the .acit
            ToolHeadData m_Data;
            /// @brief the state of the toolhead
            ToolHeadState m_State;

            /// @brief the geometries that defines the hole and used in the feedback layer
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesInfo;
            /// @brief the geometries the create the widget UI of the toolhead
            std::vector<std::shared_ptr<GOPrimitive>> m_GOPrimitivesWidget;
            /// @brief the mesh used to input and check the 6dof pose of the toolhead by the user
            GOMesh m_GOMesh;

    };
}