#pragma once

#include "Renderer/RendererTypes.h"

struct FBOSpec {
    unsigned int width;
    unsigned int height;
    GL::MagFilter magSampler = GL::MagFilter::Linear;
    GL::MagFilter minSampler = GL::MagFilter::Linear;
};

// FBO with texture & depth attatchment
class FBOTex {
   public:
    FBOTex(const FBOSpec& spec);
    ~FBOTex();

    void bindFBO() const;
    void bindTexture(unsigned int slot) const;
    void unbind() const;
    int readPixel(int x, int y);
    void setViewport() const;

    inline unsigned int getTextureId() { return m_textureId; }

   private:
    unsigned int m_fboId;
    unsigned int m_textureId;
    unsigned int m_depthBufferId;
    unsigned int m_width, m_height;
};
