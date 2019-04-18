#pragma once
#include <vector>
#include <glm/glm.hpp>


class VertexBuffer
{
private:
	
public:
	
	//VertexBuffer(std::vector<glm::vec3>* data, unsigned int size);
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	unsigned int m_RenderID;

	void Bind() const;
	void UnBind() const;

};