#pragma once
#include <vector>
#include <glm/glm.hpp>
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int rendererID);
	VertexBuffer(std::vector<glm::vec3> &data);
	VertexBuffer(std::vector<glm::vec2> &data);

	~VertexBuffer();

	void Bind();
	void Unbind();

};