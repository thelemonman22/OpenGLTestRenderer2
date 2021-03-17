#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"
#include <GL/glew.h>

//filepath of desired texture
Texture::Texture(const char* filepath)
{
	m_RendererID = 0;
	m_LocalBuffer = nullptr;
	width = 0;
	height = 0;
	m_FilePath = filepath;
	m_bpp;

	ProcessTexture();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::ProcessTexture() 
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(m_FilePath, &width, &height, &m_bpp, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	Unbind();

	if (m_LocalBuffer != NULL) {

	}stbi_image_free(m_LocalBuffer);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
