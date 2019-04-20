#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Render.h"


VertexArray::VertexArray()
{
	//create VAO
	GLCall(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	//Bind();
	//vb.Bind();
	//const auto& elements = layout.GetElements();
	//unsigned int offset = 0;
	//for (unsigned int i = 0; i < elements.size(); i++)
	//{
	//	const auto& element = elements[i];
	//	GLCall(glEnableVertexAttribArray(i));	//enable the attrib bufffer
	//	GLCall(glVertexAttribPointer(i, element.count, element.type,
	//	element.normalized, 0, 0));
	//		//element.normalized, layout.GetStride(), (const void*)offset));	//defiens the attributes of the positions array, specify the layout
	//	offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	//}
	GLCall(glEnableVertexAttribArray(m_RenderID));	//enable the attrib bufffer
	glVertexAttribPointer(vb.m_RenderID, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}