/*
	Used to initialize common libraries and
	define common macros
*/

#pragma once

// Common libraries
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <array>
#include <stdexcept>
#include <functional>
#include "Logger.h"

// Define Common Macros
#ifdef _DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x)
#endif // !_DEBUG

#define BIT(x) (1 << x)
#define BIND_EVENT_FUNC(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
