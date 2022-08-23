#pragma once

#include "AIAC/EventSys/Event.h"

namespace AIAC
{
    class AppCloseEvent : public Event
    {
    public:
        explicit AppCloseEvent()
            : Event(EventType::AppClose)
        {}

        void OnAppClose();
    };
}