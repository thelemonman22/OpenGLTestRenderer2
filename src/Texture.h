#pragma once

class Texture {
private:
	unsigned int m_RendererID;
	unsigned char* m_LocalBuffer;
	int width, height, m_bpp;
	const char* m_FilePath;

public:
	Texture(const char* filepath);
	void ProcessTexture();
	~Texture();
	void Bind();
	void Unbind();
};