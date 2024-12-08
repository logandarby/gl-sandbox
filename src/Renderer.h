#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model/Model.h"

class Renderer {
public:
	Renderer() {};
	void clear();
	void draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader);
	//void draw(const Model &model, const Shader &shader);
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer const&) = delete;
	Renderer& operator=(Renderer&&) = delete;
};
