#pragma once

#include "AIAC/Log.h"
#include "AIAC/GOSys/GOPrimitive.h"


namespace AIAC
{
    class GORegistry
    {
    public:
        GORegistry() = default;
        ~GORegistry() = default;

        void Init()
        {
            Clear();
        }
    
        // register with a template which accepts heirs of the class GOPrimitive
        template<typename T>
        void Register(std::shared_ptr<T> go)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Pushed type is not subclass of GOPrimitive!");
            m_GOMap.emplace(go->GetId(), go);
        }
        template<typename T>
        void Register(const uint32_t& id, std::shared_ptr<T> go)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Pushed type is not subclass of GOPrimitive!");
            m_GOMap.emplace(id, go);
        }

        template<typename T>
        void Unregister(std::shared_ptr<T> go)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Type to remove is not subclass of GOPrimitive!");
            m_GOMap.erase(go->GetId());
        }

        inline void Unregister(const uint32_t& id)
        {
            m_GOMap.erase(id);
        }

        // enum class ErrorCode { None = 0, NotFound = 1, NotCasted = 2 };

        // std::variant<ErrorCode,
        //             std::shared_ptr<GOPoint>,
        //             std::shared_ptr<GOLine>,
        //             std::shared_ptr<GOCircle>,
        //             std::shared_ptr<GOCylinder>,
        //             std::shared_ptr<GOPolyline>,
        //             std::shared_ptr<GOTriangle>,
        //             std::shared_ptr<GOMesh>,
        //             std::shared_ptr<GOText>> GetGO(const uint32_t& id)
        // {
        //     GOType t =  m_GOMap[id]->GetGOType();
        //     switch (t)
        //     {
        //         case GOType::GOTypePoint:
        //             return std::dynamic_pointer_cast<GOPoint>(m_GOMap[id]);
        //         case GOType::GOTypeLine:
        //             return std::dynamic_pointer_cast<GOLine>(m_GOMap[id]);
        //         case GOType::GOTypeCircle:
        //             return std::dynamic_pointer_cast<GOCircle>(m_GOMap[id]);
        //         case GOType::GOTypeCylinder:
        //             return std::dynamic_pointer_cast<GOCylinder>(m_GOMap[id]);
        //         case GOType::GOTypePolyline:
        //             return std::dynamic_pointer_cast<GOPolyline>(m_GOMap[id]);
        //         case GOType::GOTypeTriangle:
        //             return std::dynamic_pointer_cast<GOTriangle>(m_GOMap[id]);
        //         case GOType::GOTypeMesh:
        //             return std::dynamic_pointer_cast<GOMesh>(m_GOMap[id]);
        //         case GOType::GOTypeText:
        //             return std::dynamic_pointer_cast<GOText>(m_GOMap[id]);
        //         default:
        //             AIAC_WARN("Unknown type not casted from GOPrimitive.");
        //             return std::shared_ptr<GOPrimitive>();
        //     }
        // }






        std::shared_ptr<GOPoint> GetGOPoint(const uint32_t& id) { return std::dynamic_pointer_cast<GOPoint>(m_GOMap[id]); }
        std::shared_ptr<GOLine> GetGOLine(const uint32_t& id) { return std::dynamic_pointer_cast<GOLine>(m_GOMap[id]); }
        std::shared_ptr<GOCircle> GetGOCircle(const uint32_t& id) { return std::dynamic_pointer_cast<GOCircle>(m_GOMap[id]); }
        std::shared_ptr<GOCylinder> GetGOCylinder(const uint32_t& id) { return std::dynamic_pointer_cast<GOCylinder>(m_GOMap[id]); }
        std::shared_ptr<GOPolyline> GetGOPolyline(const uint32_t& id) { return std::dynamic_pointer_cast<GOPolyline>(m_GOMap[id]); }
        std::shared_ptr<GOTriangle> GetGOTriangle(const uint32_t& id) { return std::dynamic_pointer_cast<GOTriangle>(m_GOMap[id]); }
        std::shared_ptr<GOMesh> GetGOMesh(const uint32_t& id) { return std::dynamic_pointer_cast<GOMesh>(m_GOMap[id]); }
        std::shared_ptr<GOText> GetGOText(const uint32_t& id) { return std::dynamic_pointer_cast<GOText>(m_GOMap[id]); }








        inline void Clear() { m_GOMap.clear(); }
        inline uint32_t CheckIfKeyExists(uint32_t key) { return m_GOMap.count(key); }
        inline uint32_t Count() const { return m_GOMap.size(); }

    private:
        inline static std::map<uint32_t, std::shared_ptr<GOPrimitive>> m_GOMap;
    };
}