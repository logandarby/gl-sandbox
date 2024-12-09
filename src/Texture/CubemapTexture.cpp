#include "CubemapTexture.h"

#include "../core/GLCore.h"
#include "../core/Image.h"

CubemapTexture::CubemapTexture(const CubemapSource& sources) : m_rendererId{0} {
    const std::array<const std::string*, 6> srcArray = {
        &sources.right,  &sources.left,  &sources.top,
        &sources.bottom, &sources.front, &sources.back};
    GL_CALL(glGenTextures(1, &m_rendererId));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId));
    LOG_CORE_INFO("Loaded cubemap with renderer id {}", m_rendererId);

    for (unsigned int i = 0; i < srcArray.size(); i++) {
        const std::string& src = *srcArray[i];
        const Image image(src, 0, false);
        const auto& imageData = image.getImageData();
        const int width = imageData.width;
        const int height = imageData.height;
        GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                             width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                             imageData.imageData.get()));
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    unbind();
}

CubemapTexture::~CubemapTexture() {
    unbind();
    glDeleteTextures(1, &m_rendererId);
}

void CubemapTexture::bind(unsigned int slot) const {
    ASSERT(slot < MAX_TEXTURE_SLOTS);
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId))
}

void CubemapTexture::unbind() const {
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0))
}
