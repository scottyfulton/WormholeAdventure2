
#include "VertexBuffer.h"
#include "Render.h"
#include <glm/glm.hpp>

//VertexBuffer::VertexBuffer(std::vector<glm::vec3>* data, unsigned int size)
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RenderID));	//made a buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));	//assigned/bound buffer
	//for triangle
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));	//fill buffer with data, or NULL instead of GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);	//fill buffer with data, or NULL instead of GL_ARRAY_BUFFER
}

VertexBuffer::~VertexBuffer()
{

}
void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));	//assigned/bound buffer
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));	//assigned/bound buffer
}