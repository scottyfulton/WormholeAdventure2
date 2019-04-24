#pragma once
#include "vertexBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class vertexArray
{
public:
	vertexArray();
	~vertexArray();
	GLuint arrayID;
	void addBuffer(const vertexBuffer* vb, GLint attribNum, GLuint index, GLint vsize, GLenum type, GLboolean norm, GLsizei stride, const GLvoid * offset);

	void bind() const;
	void unbind() const;
};


