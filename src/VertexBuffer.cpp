#include "VertexBuffer.h"
#include "renderer.h"
#include "core/GLCore.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_rendererId(0), m_data{ data }, m_size{ size }
{
	GL_CALL(glGenBuffers(1, &m_rendererId));
	bind();
}
VertexBuffer::~VertexBuffer() {
	GL_CALL(glDeleteBuffers(1, &m_rendererId));
}

void VertexBuffer::bind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, m_size, m_data, GL_STATIC_DRAW));
}

void VertexBuffer::unbind() const {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
}
