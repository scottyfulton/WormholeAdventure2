#include "vertexArray.h"


vertexArray::vertexArray() 
{
	//create and bind buffer
	glGenVertexArrays(1, &arrayID);
	bind();
}
vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &arrayID);
}
void vertexArray::addBuffer( const vertexBuffer* vb, GLint attribNum, GLuint index, GLint vsize, GLenum type, GLboolean norm, GLsizei stride, const GLvoid * offset)
{
	//adds vbo to vao, with attribPointer, setting attrib array slot with attribNum
	vb->bind();
	glEnableVertexAttribArray(attribNum);
	glVertexAttribPointer(attribNum, vsize, type, norm, stride, offset);
}

void vertexArray::bind() const
{
	glBindVertexArray(arrayID);
}
void vertexArray::unbind() const
{
	glBindVertexArray(0);
}
