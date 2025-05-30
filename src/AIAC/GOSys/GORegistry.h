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
    
        /**
         * @brief Add a GO to the registry.
         * @param id Id of the object to register.
         * @param go Smart pointer to the object to register.
         */
        template<typename T>
        void Register(std::shared_ptr<T> go)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Pushed type is not subclass of GOPrimitive!");
            m_GOMap.emplace(go->GetId(), go);
        }

        /**
         * @brief Add a GO to the registry with a given id.
         * @param id Id of the object to register.
         * @param go Smart pointer to the object to register.
         */
        template<typename T>
        void Register(const uint32_t& id, std::shared_ptr<T> go)
        {
            static_assert(std::is_base_of<AIAC::GOPrimitive, T>::value, "Pushed type is not subclass of GOPrimitive!");
            m_GOMap.emplace(id, go);
        }

        /**
         * @brief Erase the GO from the register.
         * @param id Id of the object to erase from the register.
         */
        inline void Unregister(const uint32_t& id)
        {
            m_GOMap.erase(id);
        }

        /**
         * @brief Retrieve the GO pointer from the registry by index and template as GOObject.
         * @param id Id of the object when created.
         */
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

        /**
         * @brief Get the All GOs by category.
         * @param points A vector of all GOPoints to pass as reference.
         * @param lines A vector of all GOLines to pass as reference.
         * @param circles A vector of all GOCircles to pass as reference.
         * @param cylinders A vector of all GOCylinders to pass as reference.
         * @param polylines A vector of all GOPolylines to pass as reference.
         * @param triangles A vector of all GOTriangles to pass as reference.
         * @param texts A vector of all GOTexts to pass as reference.
         */
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

        /**
         * @brief Get all GOs of a specific type in the registry.
         */
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

        /**
         * @brief Get the All GOs as primitives.
         * @param goVector A reference vector to load with all the GOPrimitives.
         */
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

        /**
         * @brief Clear the registry from all the entries.
         */
        inline void Clear() { m_GOMap.clear(); }
        
        /**
         * @brief Check if a GO is in the registry by id.
         * @param id Id of the object to check.
         */
        inline uint32_t CheckIfKeyExists(uint32_t key) { return m_GOMap.count(key); }

        /**
         * @brief Get the total number of GOs in the registry.
         */
        inline uint32_t Count() const { return m_GOMap.size(); }

    private:
        inline static std::map<uint32_t, std::shared_ptr<GOPrimitive>> m_GOMap;
    };
}