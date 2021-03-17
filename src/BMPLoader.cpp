#define _CRT_SECURE_NO_DEPRECATE
#include <fstream>
#include <GL/glew.h>

#include "BMPLoader.h"

BMPLoader::BMPLoader(const char* imagepath) 
{
	if (readFile(imagepath)) 
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Generate mipmaps, by the way.
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

bool BMPLoader::readFile(const char* imagepath) 
{
	//Try to open file
	FILE* file = fopen(imagepath, "rb");

	if (file == NULL) 
	{
		printf("BMPLoader: Image could not be opened\n");
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) {
		printf("BMPLoader: Not a correct BMP file\n");
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("BMPLoader: Not a correct BMP file, did not start with BM \n");
		return 0;
	}
	//Read ints from the byte area ("header")
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	
	if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each red, green and blue compenent
	if (dataPos == 0) dataPos = 54; // the BMP header is done that way

	//Create a buffer
	data = new unsigned char[imageSize];
	//Read the data fom the file into the buffer
	fread(data, 1, imageSize, file);
	//Everything is in memory now, the file can be closed
	fclose(file);
	
	return 1;
}

unsigned int BMPLoader::getTextureID() 
{
	return m_TextureID;
}