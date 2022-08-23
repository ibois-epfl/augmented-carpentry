#include "aiacpch.h"
#include "AIAC/EventSys/ApplicationEvent.h"
#include "AIAC/Application.h"

namespace AIAC
{
    void AppCloseEvent::OnAppClose()
    {
        AIAC_INFO("Application closing");
        AIAC_APP.Close();
    }
}
