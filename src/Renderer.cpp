#include "Renderer.h"

#include "Model/Model.h"
#include "core/Core.h"
#include "core/GLCore.h"

void Renderer::clear() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ib,
                    const Shader& shader) {
    shader.bind();
    vao.bind();
    ib.bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, static_cast<int>(ib.getCount()),
                           GL_UNSIGNED_INT, nullptr));
}

// TODO: Doesn't work
// void Renderer::draw(const Model &model, const Shader& shader)
//{
//	shader.bind();
//	model.bind();
//	LOG_CORE_INFO(model.getIndexBufferCount());
//	GL_CALL(glDrawElements(GL_TRIANGLES,
//static_cast<int>(model.getIndexBufferCount()), GL_UNSIGNED_INT, nullptr));
//
//}
