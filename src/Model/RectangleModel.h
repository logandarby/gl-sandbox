#pragma once

#include "Renderer/BufferLayout.h"
#include "glm/glm.hpp"
#include <array>

struct RectangleModel {
    std::array<PositionWithTexture3D, 4> m_points = { {
        { { 0.5, 0, 0.5 }, { 1.0, 1.0 } },    // 0 Top right f
        { { -0.5, 0, 0.5 }, { 0.0, 1.0 } },   // 1 Top left f
        { { 0.5, 0, -0.5 }, { 1.0, 0.0 } },   // 4 Top right b
        { { -0.5, 0, -0.5 }, { 0.0, 0.0 } },  // 5 Top left b
    } };
    std::array<unsigned int, 6> m_indices = { { 0, 1, 2, 1, 2, 3 } };
    glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct RectangleModel2D {
    std::array<PositionWithTexture2D, 4> m_points = { {
        { { 1.0, 1.0 }, { 1.0, 1.0 } },
        { { -1.0, 1.0 }, { 0.0, 1.0 } },
        { { 1.0, -1.0 }, { 1.0, 0.0 } },
        { { -1.0, -1.0 }, { 0.0, 0.0 } },
    } };
    std::array<unsigned int, 6> m_indices = { { 0, 1, 2, 1, 2, 3 } };
};
