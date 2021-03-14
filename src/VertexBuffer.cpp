#include "VertexBuffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
	//GL_ARRAY_BUFFER specifies that the buffer will be used as a source for vertex data, but
	//the connection is only made when glVertexAttribPointer is called
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer()
{
	(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}