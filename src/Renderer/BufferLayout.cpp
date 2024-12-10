#include "BufferLayout.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "core/GLCore.h"
#include "renderer.h"

unsigned int BufferElement::getSizeOfType(const unsigned int type) {
    switch (type) {
        case GL_FLOAT:
            return sizeof(float);
        case GL_UNSIGNED_INT:
            return sizeof(unsigned int);
        default:
            CORE_ASSERT(false);
            return 0;
    }
}

BufferLayout::BufferLayout() : m_stride(0), m_elements() {};

template <typename T>
BufferLayout& BufferLayout::withLayout(const unsigned int count) {
    throw std::runtime_error(
        fmt::format("BufferLayout does not have implementation for "
                    "'withLayout' for type {}",
                    typeid(T).name()));
    return *this;
}

template <>
BufferLayout& BufferLayout::withLayout<PositionWithTexture2D>() {
    m_elements.push_back(
        {2, GL_FLOAT, GL_FALSE,
         (const void*)offsetof(PositionWithTexture2D, position)});
    m_elements.push_back(
        {2, GL_FLOAT, GL_FALSE,
         (const void*)offsetof(PositionWithTexture2D, textureCoords)});
    m_stride += 4 * BufferElement::getSizeOfType(GL_FLOAT);
    return *this;
}

template <>
BufferLayout& BufferLayout::withLayout<PositionWithTexture3D>() {
    m_elements.push_back({3, GL_FLOAT, GL_FALSE, nullptr});
    m_elements.push_back(
        {2, GL_FLOAT, GL_FALSE,
         (const void*)offsetof(PositionWithTexture3D, textureCoords)});
    m_stride += 5 * BufferElement::getSizeOfType(GL_FLOAT);
    return *this;
}

template <>
BufferLayout& BufferLayout::withLayout<PosNormalTexture3D>() {
    m_elements.push_back({3, GL_FLOAT, GL_FALSE, nullptr});
    m_elements.push_back(
        {2, GL_FLOAT, GL_FALSE,
         (const void*)offsetof(PosNormalTexture3D, textureCoords)});
    m_elements.push_back({3, GL_FLOAT, GL_FALSE,
                          (const void*)offsetof(PosNormalTexture3D, normal)});
    m_stride += 8 * BufferElement::getSizeOfType(GL_FLOAT);
    return *this;
}

template <>
BufferLayout& BufferLayout::withLayout<float>(const unsigned int count) {
    m_elements.push_back({count, GL_FLOAT, GL_FALSE});
    m_stride += count * BufferElement::getSizeOfType(GL_FLOAT);
    return *this;
}

template <>
BufferLayout& BufferLayout::withLayout<unsigned int>(const unsigned int count) {
    m_elements.push_back({count, GL_UNSIGNED_INT, GL_FALSE});
    m_stride += count * BufferElement::getSizeOfType(GL_UNSIGNED_INT);
    return *this;
}
