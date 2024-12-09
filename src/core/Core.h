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

// Define Common Macros
#ifdef _DEBUG
#define ASSERT(x) \
    if (!(x)) __debugbreak();
#else
#define ASSERT(x)
#endif  // !_DEBUG

#define BIT(x) (1 << x)
#define BIND_EVENT_FUNC(fn)                                     \
    [this](auto&&... args) -> decltype(auto) {                  \
        return this->fn(std::forward<decltype(args)>(args)...); \
    }
