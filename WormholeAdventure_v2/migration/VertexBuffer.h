#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"


class VertexBuffer
{
//private:
	
public:
	
	//VertexBuffer(std::vector<glm::vec3>* data, unsigned int size);
	VertexBuffer(const void* data, GLsizei size);
	~VertexBuffer();
	GLuint m_RenderID;

	void Bind() const;
	void UnBind() const;

};