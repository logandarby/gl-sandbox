// Initialize STB Image

#ifndef _DEBUG
    // Remove assertion from STB Image
    #define STBI_ASSERT(x)
#endif  // !_DEBUG

#define STBI_FAILURE_USERMSG
#include "Image.h"
#include "Core.h"
#include "stb_image.h"
#include <spdlog/fmt/fmt.h>

Image::Image(
    const std::string& filePath, const int reqComp, const bool setFlip
) {
    stbi_set_flip_vertically_on_load(setFlip);
    unsigned char* pixelData = stbi_load(
        filePath.c_str(), &m_imageData.width, &m_imageData.height,
        &m_imageData.BPP, reqComp
    );
    if (!pixelData) {
        throw std::runtime_error(fmt::format(
            "Failed to load iamge {}: {}", filePath, stbi_failure_reason()
        ));
    }
    LOG_CORE_INFO("Loaded Image {}", filePath);
    m_imageData.imageData = ImageData::deletedUniquePtr(
        pixelData, [](unsigned char* pixelData) { stbi_image_free(pixelData); }
    );
}
