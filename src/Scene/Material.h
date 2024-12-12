#pragma once

#include <glm/glm.hpp>

#include "Renderer/RendererTypes.h"

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
