#pragma once

#include "AIAC/EventSys/Event.h"


namespace AIAC
{
    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)

    private:
        unsigned int m_Width, m_Height;
    };

    class WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication  | EventCategoryWindow)
    };

    // class AppTickEvent : public Event
    // {
    // public:
    //     AppTickEvent() = default;

    //     EVENT_CLASS_TYPE(AppTick)
    //     EVENT_CLASS_CATEGORY(EventCategoryApplication)
    // };

    // class AppUpdateEvent : public Event
    // {
    // public:
    //     AppUpdateEvent() = default;

    //     EVENT_CLASS_TYPE(AppUpdate)
    //     EVENT_CLASS_CATEGORY(EventCategoryApplication)
    // };

    // class AppRenderEvent : public Event
    // {
    // public:
    //     AppRenderEvent() = default;

    //     EVENT_CLASS_TYPE(AppRender)
    //     EVENT_CLASS_CATEGORY(EventCategoryApplication)
    // };
}