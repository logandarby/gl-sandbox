#include "IndexBuffer.h"

#include "core/GLCore.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
    : m_count(count), m_rendererId(0) {
    GL_CALL(glGenBuffers(1, &m_rendererId));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data,
                         GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer() { GL_CALL(glDeleteBuffers(1, &m_rendererId)); }

void IndexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId))
}

void IndexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}
