#pragma once

#include <functional>
#include <memory>
#include <string>

struct ImageData {
    using deletedUniquePtr =
        std::unique_ptr<unsigned char, std::function<void(unsigned char*)>>;

    ImageData() = default;
    ~ImageData() = default;

    int width, height, BPP;
    deletedUniquePtr imageData;
};

class Image {
   public:
    Image(const std::string& filePath, int reqComp = 4, bool setFlip = 1);
    ~Image() = default;

    Image(Image& _) = delete;
    Image operator=(Image& _) = delete;
    Image operator=(Image&& _) = delete;

    inline const ImageData& getImageData() const { return m_imageData; }

   private:
    ImageData m_imageData;
};
