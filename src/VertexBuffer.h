#pragma once

#include <memory>

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
private:
	unsigned int m_rendererId;
	const unsigned int m_size;
	const void* m_data;
};
