#pragma once

#include "AIAC/GOSys/GOPrimitive.h"


namespace AIAC
{
    namespace GO
    {
        class GOCollection
        {
        public:
            GOCollection()
            {
                m_GOCollection = std::map<uint32_t, std::shared_ptr<GOPrimitive>>();
            };
            ~GOCollection() = default;

            uint32_t CreateKey(std::shared_ptr<GOPrimitive>& goPrimitive);
            void Add(std::shared_ptr<GOPrimitive> goPrimitive);
            void Remove(uint32_t key);
            inline uint32_t Count() const { return m_GOCollection.size(); }

        private:
            std::map<uint32_t, std::shared_ptr<GOPrimitive>> m_GOCollection;
        };


        // class GOHoles : public GOCollection
        // {
        // public:
        //     GOHoles();
        //     virtual ~GOHoles() = default;
        // };


        // class GOCuts : public GOCollection
        // {
        // public:
        //     GOCuts();
        //     virtual ~GOCuts() = default;
        // };


        // class GOTexts : public GOCollection
        // {
        // public:
        //     GOTexts();
        //     virtual ~GOTexts() = default;
        // };
    }
}