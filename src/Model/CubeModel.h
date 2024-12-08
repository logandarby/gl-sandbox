#pragma once

#include <array>
#include "glm/glm.hpp"
#include "../BufferLayout.h"

struct CubeModel {
	std::array<PositionWithTexture3D, 8> m_points = { {
			// back vertices
			{ {  0.5,  0.5,  0.5 }, { 1.0, 1.0 } }, // 0 Top right f
			{ { -0.5,  0.5,  0.5 }, { 0.0, 1.0 } }, // 1 Top left f
			{ {  0.5, -0.5,  0.5 }, { 1.0, 0.0 } }, // 2 Bottom right f
			{ { -0.5, -0.5,  0.5 }, { 1.0, 0.0 } }, // 3 Bottom left f

			// front vertices
			{ {  0.5,  0.5, -0.5 }, { 1.0, 1.0 } }, // 4 Top right b
			{ { -0.5,  0.5, -0.5 }, { 0.0, 1.0 } },	// 5 Top left b
			{ {  0.5, -0.5, -0.5 }, { 1.0, 0.0 } },	// 6 Bottom right b
			{ { -0.5, -0.5, -0.5 }, { 1.0, 0.0 } },	// 7 Bottom left b
	} };
	std::array<unsigned int, 36> m_indices = { {
			4, 5, 6,	5, 6, 7,	// front face
			0, 2, 6,	6, 0, 4,	// right face
			1, 3, 7,	1, 5, 7,	// left face
			0, 1, 4,	1, 4, 5,	// top face
			2, 3, 6,	3, 6, 7,	// bottom face
			0, 1, 2,	1, 2, 3,	// back face
	} };
	glm::mat4 modelMatrix = glm::mat4(1.0f);
};
