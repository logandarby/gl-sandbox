#pragma once

#include "../core/GLCore.h"

class Texture {
   public:
    Texture() : MAX_TEXTURE_SLOTS(GLCore::getMaxTextureSlots()) {}
    ~Texture() = default;

    virtual void bind(unsigned int slot = 0) const = 0;
    virtual void unbind() const = 0;

   protected:
    const unsigned int MAX_TEXTURE_SLOTS;
};
