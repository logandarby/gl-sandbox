#pragma once

#include <glm/glm.hpp>

#include "../core/GLCore.h"

struct Material {
    glm::vec3 specular;
    GLCore::Sampler2D texture;
    float shininess;
};

struct SpecMaterial {
    GLCore::Sampler2D specular;
    GLCore::Sampler2D texture;
    float shininess;
};
