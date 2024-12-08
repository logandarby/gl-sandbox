#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Math {

	static glm::mat3 getNormalMatrix(glm::mat4& modelMatrix) {
		return glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	}

}

