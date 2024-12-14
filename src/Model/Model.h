#pragma once

#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include <glm/glm.hpp>

class Model {
public:
    virtual void bind() const = 0;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    inline int getIndexBufferCount() const {
        return m_indexBuffer.getCount();
    }
    VertexArray m_vao;
    IndexBuffer m_indexBuffer;

protected:
    Model(IndexBuffer indexBuffer) : m_indexBuffer{ indexBuffer }, m_vao{} {}
};
