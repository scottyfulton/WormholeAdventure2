#include "vertexBuffer.h"



vertexBuffer::vertexBuffer(void* data, GLsizei size)
{	//creates the buffer space, binds, and fills data.  
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}
vertexBuffer::~vertexBuffer()
{

}
void vertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferID) ;
}
void vertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}