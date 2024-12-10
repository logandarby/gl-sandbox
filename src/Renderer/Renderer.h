#pragma once

#include "IndexBuffer.h"
#include "Model/Model.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer {
   public:
    static void clear();
    static void draw(const VertexArray& vao, const IndexBuffer& ib,
                     const Shader& shader);
};
