#pragma once
#include <memory>

#include "BufferLayout.h"
#include "VertexBuffer.h"

class VertexArray {
   public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const std::shared_ptr<VertexBuffer> vb,
                   const std::shared_ptr<BufferLayout> bl);
    void bind() const;
    void unbind() const;

   private:
    unsigned int m_rendererId;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<BufferLayout> m_bufferLayout;
};
