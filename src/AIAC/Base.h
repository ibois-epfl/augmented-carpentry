
#pragma once

#include <memory>

#if __linux__
    #define AIAC_BREAK() EXIT_FAILURE
#endif

#define AIAC_EXPAND_MACRO(x) x
#define AIAC_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define AIAC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace AIAC {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#include "AIAC/Log.h"
#include "AIAC/Assert.h"