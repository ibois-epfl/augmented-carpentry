#pragma once

#include "AIAC/Log.h"
#include "AIAC/Base.h"

#ifdef AIAC_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define AIAC_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { (msg, __VA_ARGS__); AIAC_BREAK(); } }
	#define AIAC_INTERNAL_ASSERT_WITH_MSG(type, check, ...) AIAC_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define AIAC_INTERNAL_ASSERT_NO_MSG(type, check) AIAC_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", AIAC_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define AIAC_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define AIAC_INTERNAL_ASSERT_GET_MACRO(...) AIAC_EXPAND_MACRO( AIAC_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, AIAC_INTERNAL_ASSERT_WITH_MSG, AIAC_INTERNAL_ASSERT_NO_MSG) )

    #define AIAC_ASSERT(...) AIAC_EXPAND_MACRO( AIAC_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
    #define AIAC_ASSERT(...)
#endif
