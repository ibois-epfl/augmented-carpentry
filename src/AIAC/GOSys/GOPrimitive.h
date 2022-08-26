#pragma once

namespace AIAC
{
    namespace GO
    {
        class GOPrimitive
        {
        public:
            virtual ~GOPrimitive() = default;

        private:
            uint32_t m_id;
            bool m_IsVisible;

        };



        class GOPoint : public GOPrimitive
        {
        public:
            GOPoint();
            virtual ~GOPoint() = default;
        };


        class GOLine : public GOPrimitive
        {
        public:
            GOLine();
            virtual ~GOLine() = default;
        };


        class GOCircle : public GOPrimitive
        {
        public:
            GOCircle();
            virtual ~GOCircle() = default;
        };


        class GOCylinder : public GOPrimitive
        {
        public:
            GOCylinder();
            virtual ~GOCylinder() = default;
        };


        class GOPolyline : public GOPrimitive
        {
        public:
            GOPolyline();
            virtual ~GOPolyline() = default;
        };


        class GOText : public GOPrimitive
        {
        public:
            GOText();
            virtual ~GOText() = default;
        };


        class GOMesh : public GOPrimitive
        {
        public:
            GOMesh();
            virtual ~GOMesh() = default;
        };

    }
}