

# File GORegistry.h

[**File List**](files.md) **>** [**AIAC**](dir_21da83368f7816722f2b707a7b03c84f.md) **>** [**GOSys**](dir_5f167dfbcc50bcf5ffb2c1a7f5cf90ca.md) **>** [**GORegistry.h**](GORegistry_8h.md)

[Go to the documentation of this file](GORegistry_8h.md)


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

        inline void Unregister(const uint32_t& id)
        {
            m_GOMap.erase(id);
        }

        template<typename T>
        std::shared_ptr<T> GetGO(const uint32_t& id)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Type to get is not subclass of GOPrimitive!");
            auto it = m_GOMap[id];
            // check if the static pointer cast succeed
            if (it != nullptr)
            {
                try
                {
                    return std::dynamic_pointer_cast<T>(it);
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
                        std::vector<std::shared_ptr<GOMesh>>& meshes,
                        std::vector<std::shared_ptr<GOText>>& texts)
        {
            try
            {
                for (auto& go : m_GOMap)
                {
                    if (go.second->GetType() == GOTypeFlags::_GOPoint)
                    {
                        points.push_back(std::dynamic_pointer_cast<GOPoint>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOLine)
                    {
                        lines.push_back(std::dynamic_pointer_cast<GOLine>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOCircle)
                    {
                        circles.push_back(std::dynamic_pointer_cast<GOCircle>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOCylinder)
                    {
                        cylinders.push_back(std::dynamic_pointer_cast<GOCylinder>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOPolyline)
                    {
                        polylines.push_back(std::dynamic_pointer_cast<GOPolyline>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOTriangle)
                    {
                        triangles.push_back(std::dynamic_pointer_cast<GOTriangle>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOMesh)
                    {
                        meshes.push_back(std::dynamic_pointer_cast<GOMesh>(go.second));
                    }
                    else if (go.second->GetType() == GOTypeFlags::_GOText)
                    {
                        texts.push_back(std::dynamic_pointer_cast<GOText>(go.second));
                    }
                }
            }
            catch (const std::bad_cast& e) { AIAC_ERROR("Bad cast exception: {}", e.what()); }
        }

        template<typename T>
        std::vector<std::shared_ptr<T>> GetAllGOs()
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Type to get is not subclass of GOPrimitive!");
            std::vector<std::shared_ptr<T>> goVector;
            for (auto& go : m_GOMap)
            {
                if (go.second->GetType() == GOTypeFlags::_GOPoint)
                {
                    goVector.push_back(std::dynamic_pointer_cast<T>(go.second));
                }
            }
            return goVector;
        }

        void GetAllGOs(std::vector<std::shared_ptr<GOPrimitive>>& goVector)
        {
            try
            {
                for (auto& go : m_GOMap)
                {
                    goVector.push_back(go.second);
                }
            }
            catch (const std::bad_cast& e) { AIAC_ERROR("Bad cast exception: {}", e.what()); }
        }

        inline void Clear() { m_GOMap.clear(); }
        
        inline uint32_t CheckIfKeyExists(uint32_t key) { return m_GOMap.count(key); }

        inline uint32_t Count() const { return m_GOMap.size(); }

    private:
        inline static std::map<uint32_t, std::shared_ptr<GOPrimitive>> m_GOMap;
    };
}
```


