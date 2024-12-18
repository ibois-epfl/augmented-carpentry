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

#include "AIAC/Base.h"
#include "eventpp/eventqueue.h"
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventpolicies.h"


namespace AIAC
{
    enum class EventType
    {
        None = 0,
        AppClose,
        SLAMMapLoaded, SLAMVocabularyLoaded, SLAMStartMapping, SLAMStopMapping,
        SLAMCombineMapEvent,
        CameraCalibrationLoaded
        /* add types of events here */
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication =              BIT(0),
        EventCategorySLAM =                     BIT(1),
        EventCategoryCamera =                   BIT(2)
        /* add event category here */
    };

    class Event
    {
    public:
        explicit Event(const EventType type, const EventCategory category = EventCategory::None, int32_t priority = 0)
            : m_Type(type), m_Category(category), m_Priority(priority)
        {}
        virtual ~Event() = default;

        EventType GetType() const { return m_Type; }
        EventCategory GetCategory() const { return m_Category; }

    private:
        EventType m_Type;
        EventCategory m_Category;
        int32_t m_Priority;
    };

    using EventPointer = std::shared_ptr<Event>;

    struct EventCompare
    {
        template <typename T>
        bool operator() (const T & a, const T & b) const
        {
            return a->GetPriority() > b->GetPriority();
        }
    };

    struct EventPolicy
    {
        template <typename Item>
        using PrioriQueueListtyQueue = std::priority_queue<Item, std::vector<Item>, EventCompare>;

        static EventType GetEvent(const EventPointer& event) {
            return event->GetType();
        }

        static EventCategory GetCategory(const EventPointer& event) {
            return event->GetCategory();
        }
    };

}
