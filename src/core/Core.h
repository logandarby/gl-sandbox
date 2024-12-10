/*
        Used to initialize common libraries and
        define common macros
*/

#pragma once

// Common libraries
#include <array>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Logger.h"

// Define Common Types
template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T>
using WeakRef = std::weak_ptr<T>;

// Define Common Macros
#ifdef _DEBUG
#define CORE_ASSERT(x) \
    if (!(x)) __debugbreak();
#else
#define CORE_ASSERT(x)
#endif  // !_DEBUG

#define BIT(x) (1 << x)
#define BIND_EVENT_FUNC(fn)                                     \
    [this](auto&&... args) -> decltype(auto) {                  \
        return this->fn(std::forward<decltype(args)>(args)...); \
    }
