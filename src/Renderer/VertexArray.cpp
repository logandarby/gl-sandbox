#include "VertexArray.h"
#include "renderer.h"
#include "core/GLCore.h"

VertexArray::VertexArray() : m_rendererId(0) {
    GL_CALL(glGenVertexArrays(1, &m_rendererId));
}

VertexArray::~VertexArray() {
    GL_CALL(glDeleteVertexArrays(1, &m_rendererId));
}

void VertexArray::bind() const {
    GL_CALL(glBindVertexArray(m_rendererId));
}

void VertexArray::unbind() const {
    GL_CALL(glBindVertexArray(0));
}

void VertexArray::addBuffer(
    const std::shared_ptr<VertexBuffer> vb,
    const std::shared_ptr<BufferLayout> bl
) {
    m_vertexBuffer = vb;
    m_bufferLayout = bl;
    this->bind();
    vb->bind();
    const auto& elements = bl->getElements();
    intptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i));
        CORE_ASSERT(1 <= element.count && element.count <= 4);
        GL_CALL(glVertexAttribPointer(
            i, element.count, element.type, element.normalized, bl->getStride(),
            reinterpret_cast<const void*>(offset)
        ));
        GL_CALL(glEnableVertexAttribArray(0));
        offset += element.count * BufferElement::getSizeOfType(element.type);
    }
}
