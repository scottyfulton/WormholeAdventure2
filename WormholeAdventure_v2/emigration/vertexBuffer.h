#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class vertexBuffer
{
public:
	vertexBuffer(void* data, GLsizei size);
	~vertexBuffer();
	GLuint bufferID;
	void bind()const ;
	void unbind()const;

};

