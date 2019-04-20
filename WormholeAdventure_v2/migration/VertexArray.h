#pragma once
#include "VertexBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class VertexBufferLayout;

class VertexArray
{

public:
	VertexArray();
	~VertexArray();

	GLuint m_RenderID;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};