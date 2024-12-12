/*
    Used to properly import GL - related libraries and
    macros in their desired cpp files
*/
#pragma once

#include "Core.h"

// Initialize GL once and properly

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Should be used for every call to the GL API to
// Get proper openGL error logging
#define GL_CALL(x)          \
    GLCore::glClearError(); \
    x;                      \
    CORE_ASSERT(GLCore::glLogError(#x, __FILE__, __LINE__));

namespace GLCore {
void glClearError();
bool glLogError(const char* function, const char* file, const int line);
}  // namespace GLCore
