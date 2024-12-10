#pragma once

#include <array>
#include <vector>

#pragma pack(push, 1)
struct PositionWithTexture2D {
    float position[2];
    float textureCoords[2];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PositionWithTexture3D {
    float position[3];
    float textureCoords[2];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PosNormalTexture3D {
    float position[3];
    float textureCoords[2];
    float normal[3];
};
#pragma pack(pop)

struct BufferElement {
    const unsigned int count;
    const unsigned int type;
    const unsigned char normalized;
    const void* offset = nullptr;

    static unsigned int getSizeOfType(unsigned int type);
};

class BufferLayout {
   public:
    BufferLayout();

    template <typename T>
    BufferLayout& withLayout();
    template <typename T>
    BufferLayout& withLayout(const unsigned int count);

    inline const std::vector<BufferElement>& getElements() const {
        return m_elements;
    }
    inline unsigned int getStride() const { return m_stride; }

   private:
    std::vector<BufferElement> m_elements;
    unsigned int m_stride;
};
