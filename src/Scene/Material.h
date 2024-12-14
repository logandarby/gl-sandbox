#pragma once

#include "Renderer/RendererTypes.h"
#include <glm/glm.hpp>

struct Material {
    glm::vec3 specular;
    GL::Sampler2D texture;
    float shininess;
};

struct SpecMaterial {
    GL::Sampler2D specular;
    GL::Sampler2D texture;
    float shininess;
};
