#pragma once

#include "Texture.h"
#include <string>

struct CubemapSource {
    const std::string right;
    const std::string left;
    const std::string top;
    const std::string bottom;
    const std::string back;
    const std::string front;
};

class CubemapTexture : public Texture {
public:
    CubemapTexture(const CubemapSource& sources);
    ~CubemapTexture();

    virtual void bind(unsigned int slot = 0) const override;
    virtual void unbind() const override;

private:
    unsigned int m_rendererId;
};
