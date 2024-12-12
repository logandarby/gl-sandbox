#include "RendererTypes.h"

#include "Core/GLCore.h"

unsigned int GL::getMagFilter(const MagFilter &m) {
    switch (m) {
    case MagFilter::Nearest:
        return GL_NEAREST;
    case MagFilter::Linear:
        return GL_LINEAR;
    }
    return GL_LINEAR;
}

unsigned int GL::getCursorMode(const CursorMode &m) {
    switch (m) {
    case CursorMode::Disabled:
        return GLFW_CURSOR_DISABLED;
    case CursorMode::Normal:
        return GLFW_CURSOR_NORMAL;
    }
    return GLFW_CURSOR_NORMAL;
}

unsigned int GL::getKeyCode(const KeyCode &key) {
    switch (key) {
#define X(a)                                                                                       \
    case KeyCode::a:                                                                               \
        return GLFW_KEY_##a;
        KEY_PRESSES
#undef X
    default:
        return GLFW_KEY_UNKNOWN;
    }
}

GL::KeyCode GL::getKeyCodeFromInt(int k) {
    switch (k) {
#define X(a)                                                                                       \
    case GLFW_KEY_##a:                                                                             \
        return KeyCode::a;
        KEY_PRESSES
#undef X
    default:
        return KeyCode::UNKNOWN;
    }
}
