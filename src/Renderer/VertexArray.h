#pragma once
#include "BufferLayout.h"
#include "VertexBuffer.h"
#include <memory>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(
        const std::shared_ptr<VertexBuffer> vb,
        const std::shared_ptr<BufferLayout> bl
    );
    static inline VertexArray withBuffer(
        const std::shared_ptr<VertexBuffer> vb,
        const std::shared_ptr<BufferLayout> bl
    ) {
        VertexArray va;
        va.addBuffer(vb, bl);
        return va;
    }

    void bind() const;
    void unbind() const;

private:
    unsigned int m_rendererId;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<BufferLayout> m_bufferLayout;
};
