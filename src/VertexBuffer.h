#pragma once
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int rendererID);
	~VertexBuffer();

	void Bind();
	void Unbind();

};