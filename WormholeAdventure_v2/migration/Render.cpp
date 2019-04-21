
#include "Render.h"
#include <iostream>

//********************************************************************//
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
//********************************************************************//
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL Error: [look up in glew.h] (" << std::hex << error << ") in: \n " <<
			function << " " << file << ":" << std::dec << line << std::endl;
		return false;
	}
	return true;
}

void Render::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Render::Draw(const VertexArray& va, const IndexBuffer& ib, const myShader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}