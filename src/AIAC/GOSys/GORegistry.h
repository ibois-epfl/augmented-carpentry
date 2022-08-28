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

        template<typename T>
        std::shared_ptr<T> GetGO(const uint32_t& id)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Type to get is not subclass of GOPrimitive!");
            auto it = m_GOMap[id];
            // check if the static poitner cast succed
            if (it != nullptr)
            {
                try
                {
                    return std::static_pointer_cast<T>(it);
                }
                catch (const std::bad_cast& e)
                {
                    AIAC_ERROR("Bad cast exception: {}", e.what());
                    return nullptr;
                }
            }
            else { AIAC_ERROR("Could not get GO with id: {}", id); return nullptr; }
        }


        void GetAllGOs(std::vector<std::shared_ptr<GOPoint>>& points,
                        std::vector<std::shared_ptr<GOLine>>& lines,
                        std::vector<std::shared_ptr<GOCircle>>& circles,
                        std::vector<std::shared_ptr<GOCylinder>>& cylinders,
                        std::vector<std::shared_ptr<GOPolyline>>& polylines,
                        std::vector<std::shared_ptr<GOTriangle>>& triangles,
                        std::vector<std::shared_ptr<GOText>>& texts)
        {
            for (auto& go : m_GOMap)
            {
                if (go.second->GetType() == GOTypeFlags::_GOPoint)
                {
                    points.push_back(std::static_pointer_cast<GOPoint>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOLine)
                {
                    lines.push_back(std::static_pointer_cast<GOLine>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOCircle)
                {
                    circles.push_back(std::static_pointer_cast<GOCircle>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOCylinder)
                {
                    cylinders.push_back(std::static_pointer_cast<GOCylinder>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOPolyline)
                {
                    polylines.push_back(std::static_pointer_cast<GOPolyline>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOTriangle)
                {
                    triangles.push_back(std::static_pointer_cast<GOTriangle>(go.second));
                }
                else if (go.second->GetType() == GOTypeFlags::_GOText)
                {
                    texts.push_back(std::static_pointer_cast<GOText>(go.second));
                }
            }
        }

        inline void Clear() { m_GOMap.clear(); }
        inline uint32_t CheckIfKeyExists(uint32_t key) { return m_GOMap.count(key); }
        inline uint32_t Count() const { return m_GOMap.size(); }

    private:
        inline static std::map<uint32_t, std::shared_ptr<GOPrimitive>> m_GOMap;
    };
}