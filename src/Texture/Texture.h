#pragma once

#include "Renderer/Renderer.h"

class Texture {
public:
    Texture() : MAX_TEXTURE_SLOTS(Renderer::getMaxTextureSlots()) {}
    ~Texture() = default;

    virtual void bind(unsigned int slot = 0) const = 0;
    virtual void unbind() const = 0;

protected:
    const unsigned int MAX_TEXTURE_SLOTS;
};
