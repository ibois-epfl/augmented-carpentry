#pragma once

#include "AIAC/Log.h"
#include <filesystem>


#ifdef AIAC_ENABLE_ASSERTS
    #define AIAC_ASSERT(...) AIAC_EXPAND_MACRO( AIAC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
    #define AIAC_ASSERT(...)
#endif